#ifndef QUADRANGLE_HPP
#define QUADRANGLE_HPP

#include "shape.hpp"

class Quadrangle : public ShapeHelper <Shape>
{
	Q_OBJECT
public:
	Quadrangle();
	virtual QString getName();

public slots:
	void setBeamLength(int id, double length);
	void setBeamLength(int id);
	void setBeamAngle(int id);

protected:
	virtual QWidget* onCreateControlWidget(QWidget *parent = 0);
	virtual void mydraw(QPainter &painter);

	qreal m_angles[4];
	qreal m_lengths[4];
};

#endif
