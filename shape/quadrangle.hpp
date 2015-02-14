#ifndef QUADRANGLE_HPP
#define QUADRANGLE_HPP

#include "shape.hpp"

class Quadrangle : public Shape
{
public:
	Quadrangle();
	virtual QString getName();
private:
	QWidget* onCreateControlWidget(QWidget *parent = 0);
	virtual void mydraw(QPainter &painter);

	qreal m_angles[4];
	qreal m_lengths[4];
};

#endif
