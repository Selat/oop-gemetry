#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include <QWidget>

#include "shape.hpp"

class Circle : public Shape
{
	Q_OBJECT
public:
	Circle();
	QString getName();

public slots:
	void setRadius(double val);

protected:
	QWidget* onCreateControlWidget(QWidget *parent = 0);

	void mydraw(QPainter &painter);
	qreal m_radius;
};

#endif
