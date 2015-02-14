#ifndef QUADRANGLEDIAGONALS_HPP
#define QUADRANGLEDIAGONALS_HPP

#include "quadrangle.hpp"

class QuadrangleDiagonals : public Quadrangle
{
	Q_OBJECT
public:
	QuadrangleDiagonals();
	virtual QString getName();

protected:
	QWidget* onCreateControlWidget(QWidget *parent = 0);
	virtual void mydraw(QPainter &painter);
};

#endif
