#ifndef QUADRANGLEFILLED_HPP
#define QUADRANGLEFILLED_HPP

#include <QColor>

#include "quadranglediagonals.hpp"

class QuadrangleFilled : public ShapeHelper <QuadrangleDiagonals>
{
	Q_OBJECT
public:
	QuadrangleFilled();
	virtual QString getName();

public slots:
	void setColor(int id);

protected:
	virtual QWidget* onCreateControlWidget(QWidget *parent = 0);
	virtual void mydraw(QPainter &painter);


	QWidget *m_parent;
	QColor m_colors[4];
};

#endif
