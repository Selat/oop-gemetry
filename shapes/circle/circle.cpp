#include <QPushButton>
#include <QDebug>

#include "circle.hpp"
#include "slidercontrol.hpp"

Circle::Circle() :
	m_radius(0.5)
{
}

QString Circle::getName()
{
	return "Circle";
}

void Circle::setRadius(double val)
{
	m_radius = val;
}

void Circle::mydraw(QPainter &painter)
{
	painter.setBrush(Qt::black);
	painter.setBrush(Qt::NoBrush);
	painter.drawEllipse(QPointF(0.0, 0.0), m_radius, m_radius);
}

QWidget* Circle::onCreateControlWidget(QWidget *parent)
{
	SliderControl *rad_control = new SliderControl(parent);
	rad_control->setMinimum(0.1);
	rad_control->setMaximum(1.0);
	rad_control->setValue(0.5);
	connect(rad_control, SIGNAL(valueChanged(double)), this, SLOT(setRadius(double)));
	connect(rad_control, SIGNAL(valueChanged(double)), parent, SLOT(repaint()));
	return rad_control;
}

extern "C" TEST_COMMON_DLLSPEC void* createShape()
{
	return new Circle();
}
