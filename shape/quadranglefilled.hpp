#ifndef QUADRANGLEFILLED_HPP
#define QUADRANGLEFILLED_HPP

#include <QColor>

#include "quadranglediagonals.hpp"

class QuadrangleFilled : public QuadrangleDiagonals
{
	Q_OBJECT
public:
	QuadrangleFilled();
	virtual QString getName();

public slots:
	void setColor(int id);

protected:
	QWidget* onCreateControlWidget(QWidget *parent = 0);
	virtual void mydraw(QPainter &painter);


	QWidget *m_parent;
	QColor m_colors[4];
};

#endif
