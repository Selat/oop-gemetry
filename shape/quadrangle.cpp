#include <QDial>
#include <QGridLayout>

#include <cmath>

#include "quadrangle.hpp"
#include "slidercontrol.hpp"

Quadrangle::Quadrangle()
{
	m_shape_controllers.push_back((ShapeControl)&Quadrangle::onCreateControlWidget);

	for(int i = 0; i < 4; ++i) {
		m_lengths[i] = 0.3;
		m_angles[i] = M_PI / 2.0 * i;
	}
}

QString Quadrangle::getName()
{
	return "Quadrangle";
}

QWidget* Quadrangle::onCreateControlWidget(QWidget *parent)
{
	QWidget *widget = new QWidget;
	QGridLayout *layout = new QGridLayout;
	for(int i = 0; i < 2; ++i) {
		for(int j = 0; j < 2; ++j) {
			SliderControl *length = new SliderControl(parent);
			length->setMinimum(0.1);
			length->setMaximum(1.0);
			length->setValue(0.3);
			layout->addWidget(length, 2 * i, j);

			QDial *angle = new QDial(widget);
			angle->setNotchTarget(10.0);
			angle->setNotchesVisible(true);
			angle->setWrapping(true);
			angle->setMaximum(359);
			int angle = -m_angles[i * 2 + j] * 180.0;
			angle->setValue(270);
			layout->addWidget(angle, 2 * i + 1, j);
		}
	}
	widget->setLayout(layout);
	return widget;
}

void Quadrangle::mydraw(QPainter &painter)
{
	QPointF points[4];
	for(int i = 0; i < 4; ++i) {
		points[i].setX(m_lengths[i] * cos(m_angles[i]));
		points[i].setY(m_lengths[i] * sin(m_angles[i]));
	}
	for(int i = 0; i < 3; ++i) {
		painter.drawLine(points[i], points[i + 1]);
	}
	painter.drawLine(points[0], points[3]);
}
