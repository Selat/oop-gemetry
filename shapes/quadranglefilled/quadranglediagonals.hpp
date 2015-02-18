#ifndef QUADRANGLEDIAGONALS_HPP
#define QUADRANGLEDIAGONALS_HPP

#include "quadrangle.hpp"

class QuadrangleDiagonals : public ShapeHelper <Quadrangle>
{
	Q_OBJECT
public:
	QuadrangleDiagonals();
	virtual QString getName();

protected:
	virtual QWidget* onCreateControlWidget(QWidget *parent = 0);
	virtual void mydraw(QPainter &painter);
};

#endif
