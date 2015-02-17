#include <QDebug>
#include <QVBoxLayout>
#include <QPushButton>
#include <QColorDialog>

#include <cmath>

#include "filledcircle.hpp"
#include "slidercontrol.hpp"

FilledCircle::FilledCircle() :
	m_parent(nullptr),
	m_inner_radius(0.5),
	m_color(Qt::red)
{
}

QString FilledCircle::getName()
{
	return "Filled circle";
}

void FilledCircle::setInnerRadius(double r)
{
	m_inner_radius = r;
}

void FilledCircle::setColor(const QColor &color)
{
	m_color = color;
}

void FilledCircle::setColor()
{
	m_color = QColorDialog::getColor(m_color, m_parent, "Color select");
}

QWidget* FilledCircle::onCreateControlWidget(QWidget *parent)
{
	m_parent = parent;
	QWidget *widget = new QWidget;
	QVBoxLayout *layout = new QVBoxLayout;
	SliderControl *inrad_control = new SliderControl(parent);
	inrad_control->setMinimum(0.1);
	inrad_control->setMaximum(1.0);
	inrad_control->setValue(0.5);
	layout->addWidget(inrad_control);

	QPushButton *color = new QPushButton("Set color", parent);
	layout->addWidget(color);
	widget->setLayout(layout);

	connect(inrad_control, SIGNAL(valueChanged(double)), this, SLOT(setInnerRadius(double)));
	connect(inrad_control, SIGNAL(valueChanged(double)), parent, SLOT(repaint()));
	connect(color, SIGNAL(clicked()), this, SLOT(setColor()));
	connect(color, SIGNAL(clicked()), parent, SLOT(repaint()));
	return widget;
}

void FilledCircle::mydraw(QPainter &painter)
{
	double m_radius2 = m_radius * m_inner_radius;
	QPointF center(0.0, 0.0);
	QPointF circle_point(m_radius, 0.0);
	painter.setBrush(m_color);
	painter.drawEllipse(center, m_radius, m_radius);
	painter.setBrush(Qt::white);
	painter.drawEllipse(center, m_radius2, m_radius2);
	painter.drawLine(center, circle_point);
}
