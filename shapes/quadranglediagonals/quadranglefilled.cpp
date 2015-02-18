#include <QGridLayout>
#include <QSignalMapper>
#include <QPushButton>
#include <QColorDialog>

#include "quadranglefilled.hpp"

QuadrangleFilled::QuadrangleFilled()
{
	for(int i = 0; i < 4; ++i) {
		m_colors[i] = Qt::red;
	}
}

QString QuadrangleFilled::getName()
{
	return "Quadrangle with filled";
}

void QuadrangleFilled::setColor(int id)
{
	m_colors[id] = QColorDialog::getColor(m_colors[id], m_parent, "Color");
}

QWidget* QuadrangleFilled::onCreateControlWidget(QWidget *parent)
{
	m_parent = parent;
	QWidget *widget = new QWidget;
	QGridLayout *layout = new QGridLayout;

	QSignalMapper *color_mapper = new QSignalMapper(parent);

	for(int i = 0; i < 2; ++i) {
		for(int j = 0; j < 2; ++j) {
			QPushButton *color = new QPushButton("Color", parent);
			layout->addWidget(color, i, j);

			connect(color, SIGNAL(clicked()), color_mapper, SLOT(map()));
			color_mapper->setMapping(color, i * 2 + j);
		}
	}

	connect(color_mapper, SIGNAL(mapped(int)), this, SLOT(setColor(int)));
	connect(color_mapper, SIGNAL(mapped(int)), parent, SLOT(repaint()));

	widget->setLayout(layout);
	return widget;
}

void QuadrangleFilled::mydraw(QPainter &painter)
{
	QPointF points[4];
	QPointF center;
	QPointF poly[3];
	painter.setPen(Qt::black);
	for(int i = 0; i < 4; ++i) {
		points[i].setX(m_lengths[i] * cos(m_angles[i]));
		points[i].setY(m_lengths[i] * sin(m_angles[i]));
	}
	// Draw outline of the figure
	for(int i = 0; i < 3; ++i) {
		painter.drawLine(points[i], points[i + 1]);
	}
	painter.drawLine(points[0], points[3]);

	// Draw diagonals
	for(int i = 0; i < 4; ++i) {
		painter.drawLine(center, points[i]);
	}

	poly[0] = center;
	for(int i = 0; i < 4; ++i) {
		painter.setBrush(QBrush(m_colors[i]));
		poly[1] = points[i];
		poly[2] = points[(i + 1) % 4];
		painter.drawPolygon(poly, 3);
	}
}
