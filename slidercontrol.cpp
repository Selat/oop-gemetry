#include <QLineEdit>
#include <QSlider>
#include <QVBoxLayout>
#include <QIntValidator>
#include <QTextStream>
#include <QDebug>

#include "slidercontrol.hpp"

SliderControl::SliderControl(QWidget *parent) :
	QWidget(parent)
{
	QVBoxLayout *layout = new QVBoxLayout;
	m_text = new QLineEdit(this);
	m_text->setValidator(new QDoubleValidator(-1.0, 1.0, 5, this));
	layout->addWidget(m_text);
	m_slider = new QSlider(Qt::Horizontal, this);
	m_slider->setMinimum(1);
	m_slider->setMaximum(1000);
	layout->addWidget(m_slider);
	layout->insertStretch(-1, 1);
	setLayout(layout);

	connect(m_slider, SIGNAL(valueChanged(int)), this, SLOT(setValue(int)));
	connect(m_text, SIGNAL(textChanged(const QString&)), this, SLOT(textChanged(const QString&)));
	setValue(50);
}

void SliderControl::setMinimum(double val)
{
	const QDoubleValidator *validator = dynamic_cast<const QDoubleValidator*>(m_text->validator());
	double dmin = val;
	double dmax = validator->top();
	m_text->setValidator(new QDoubleValidator(dmin, dmax, 5, this));
}

void SliderControl::setMaximum(double val)
{
	const QDoubleValidator *validator = dynamic_cast<const QDoubleValidator*>(m_text->validator());
	double dmin = validator->bottom();
	double dmax = val;
	m_text->setValidator(new QDoubleValidator(dmin, dmax, 5, this));
}

double SliderControl::getMinimum()
{
	const QDoubleValidator *validator = dynamic_cast<const QDoubleValidator*>(m_text->validator());
	return validator->bottom();
}

double SliderControl::getMaximum()
{
	const QDoubleValidator *validator = dynamic_cast<const QDoubleValidator*>(m_text->validator());
	return validator->top();
}

double SliderControl::getValue()
{
	double res;
	QString text = m_text->text();
	QTextStream stream(&text);
	stream >> res;
	return res;
}

void SliderControl::setValue(int val)
{
	int imin = m_slider->minimum();
	int imax = m_slider->maximum();
	const QDoubleValidator *validator = dynamic_cast<const QDoubleValidator*>(m_text->validator());
	double dmin = validator->bottom();
	double dmax = validator->top();
	double ratio = static_cast<double>(val - imin) / (imax - imin);
	double dval = ratio * (dmax - dmin) + dmin;
	setTextValue(dval);
}

void SliderControl::setValue(double val)
{
	setTextValue(val);
	int imin = m_slider->minimum();
	int imax = m_slider->maximum();
	const QDoubleValidator *validator = dynamic_cast<const QDoubleValidator*>(m_text->validator());
	double dmin = validator->bottom();
	double dmax = validator->top();
	double ratio = static_cast<double>(val - dmin) / (dmax - dmin);
	int ival = ratio * (imax - imin) + imin;
	m_slider->setValue(ival);
}

void SliderControl::textChanged(const QString &text)
{
	QString tmp(text);
	QTextStream stream(&tmp);
	double val;
	stream >> val;
	setValue(val);
}

void SliderControl::setTextValue(double val)
{
	QString res;
	QTextStream stream(&res);
	stream.setRealNumberPrecision(2);
	stream << val;
	m_text->setText(res);

	emit valueChanged(val);
}
