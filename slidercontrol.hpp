#ifndef SLIDERCONTROL_HPP
#define SLIDERCONTROL_HPP

#include <QWidget>
#include <QString>

class QSlider;
class QLineEdit;

class SliderControl : public QWidget
{
	Q_OBJECT
public:
	SliderControl(QWidget *parent = 0);

	void setMinimum(double val);
	void setMaximum(double val);

	double getMinimum();
	double getMaximum();
	double getValue();

public slots:
	void setValue(int);
	void setValue(double);
	void textChanged(const QString &text);

signals:
	void valueChanged(double);

private:
	void setTextValue(double val);

	QSlider *m_slider;
	QLineEdit *m_text;
};

#endif
