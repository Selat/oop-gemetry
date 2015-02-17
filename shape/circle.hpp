#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include <QWidget>

#include "shape.hpp"

class QLayout;

class Circle : public ShapeHelper <Shape>
{
	Q_OBJECT
public:
	Circle();
	virtual QString getName();

public slots:
	void setRadius(double val);

protected:
	virtual QWidget* onCreateControlWidget(QWidget *parent = 0);

	void mydraw(QPainter &painter);
	qreal m_radius;
};

#endif
