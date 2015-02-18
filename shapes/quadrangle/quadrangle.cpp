#include <QDial>
#include <QGridLayout>
#include <QDebug>
#include <QSignalMapper>

#include <cmath>

#include "quadrangle.hpp"
#include "slidercontrol.hpp"

Quadrangle::Quadrangle()
{
	for(int i = 0; i < 4; ++i) {
		m_lengths[i] = 0.3;
		m_angles[i] = M_PI / 2.0 * i;
	}
}

QString Quadrangle::getName()
{
	return "Quadrangle";
}

void Quadrangle::setBeamLength(int id, double length)
{
	m_lengths[id] = length;
}

void Quadrangle::setBeamLength(int id)
{
	QSignalMapper *signal_mapper = &dynamic_cast<QSignalMapper&>(*sender());
	SliderControl *length = &dynamic_cast<SliderControl&>(*signal_mapper->mapping(id));
	m_lengths[id] = length->getValue();
}

void Quadrangle::setBeamAngle(int id)
{
	QSignalMapper *signal_mapper = &dynamic_cast<QSignalMapper&>(*sender());
	QDial *angle_widget = &dynamic_cast<QDial&>(*signal_mapper->mapping(id));
	int angle = angle_widget->value();
	angle = -angle;
	angle -= 90;
	angle += 360;
	if(angle < 0) {
		angle += 360;
	}
	m_angles[id] = (angle / 180.0) * M_PI;
}

QWidget* Quadrangle::onCreateControlWidget(QWidget *parent)
{
	QWidget *widget = new QWidget;
	QGridLayout *layout = new QGridLayout;

	QSignalMapper *length_mapper = new QSignalMapper(parent);
	QSignalMapper *angle_mapper = new QSignalMapper(parent);

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
			int angle_val = -m_angles[i * 2 + j] / M_PI * 180.0;
			angle_val += 270;
			if(angle_val < 0) {
				angle_val += 360;
			}
			angle->setValue(angle_val);
			layout->addWidget(angle, 2 * i + 1, j);

			connect(length, SIGNAL(valueChanged(double)), length_mapper, SLOT(map()));
			length_mapper->setMapping(length, i * 2 + j);
			connect(angle, SIGNAL(valueChanged(int)), angle_mapper, SLOT(map()));
			angle_mapper->setMapping(angle, i * 2 + j);
		}
	}

	connect(length_mapper, SIGNAL(mapped(int)), this, SLOT(setBeamLength(int)));
	connect(length_mapper, SIGNAL(mapped(int)), parent, SLOT(repaint()));
	connect(angle_mapper, SIGNAL(mapped(int)), this, SLOT(setBeamAngle(int)));
	connect(angle_mapper, SIGNAL(mapped(int)), parent, SLOT(repaint()));

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

extern "C" TEST_COMMON_DLLSPEC void* createShape()
{
	return new Quadrangle();
}
