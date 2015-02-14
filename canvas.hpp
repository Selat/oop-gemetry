#ifndef CANVAS_HPP
#define CANVAS_HPP

#include <QWidget>

class Shape;

class Canvas : public QWidget
{
public:
	Canvas(QWidget *parent = 0);
	void setCurrentFigure(Shape *shape);
protected:
	void paintEvent(QPaintEvent *event);
private:
	Shape *m_cur_figure;

};

#endif
