#ifndef SLIDERCONTROL_HPP
#define SLIDERCONTROL_HPP

#include <QWidget>

class QSlider;
class QLineEdit;

class SliderControl : public QWidget
{
	Q_OBJECT
public:
	SliderControl(QWidget *parent = 0);

	void setMinimum(double val);
	void setMaximum(double val);

public slots:
	void setValue(int);
	void setValue(double);

signals:
	void valueChanged(double);

private:
	void setTextValue(double val);

	QSlider *m_slider;
	QLineEdit *m_text;
};

#endif
