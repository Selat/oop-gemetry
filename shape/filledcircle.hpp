#ifndef FILLEDCIRCLE_HPP
#define FILLEDCIRCLE_HPP

#include <QColor>

#include "circle.hpp"

class FilledCircle : public ShapeHelper <Circle>
{
	Q_OBJECT
public:
	FilledCircle();
	QString getName();

public slots:
	void setInnerRadius(double r);
	void setColor(const QColor &color);
	void setColor();

protected:
	virtual QWidget* onCreateControlWidget(QWidget *parent = 0);

	void mydraw(QPainter &painter);

	QWidget* m_parent;

	qreal m_inner_radius;
	QColor m_color;
};

#endif
