#include <QPainter>
#include <QDebug>

#include "canvas.hpp"
#include "shape/shape.hpp"

Canvas::Canvas(QWidget *parent) :
	QWidget(parent),
	m_cur_figure(NULL)
{
//	setMinimumWidth(500);
	setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding));
}

void Canvas::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);
	painter.setBrush(QBrush(Qt::white));
	painter.setRenderHint(QPainter::Antialiasing, true);
	painter.drawRect(0, 0, width(), height());
	QTransform transform;
	qreal w_2 = width() / 2;
	qreal h_2 = height() / 2;
	transform.translate(w_2, h_2);
	qreal ratio = w_2 / h_2;
	if(ratio > 1.0) {
		transform.scale(w_2 / ratio, -h_2);
	} else {
		transform.scale(w_2, -h_2 * ratio);
	}
	painter.setTransform(transform);
	if(m_cur_figure != NULL) {
		m_cur_figure->draw(painter);
	}
}

void Canvas::setCurrentFigure(Shape *shape)
{
	m_cur_figure = shape;
}
