#ifndef SHAPE_HPP
#define SHAPE_HPP

#include <QtGlobal>
#include <QPainter>
#include <QPointF>
#include <QString>
#include <QLayout>
#include <QDebug>
#include <QFrame>

#include <cmath>

#include "slidercontrol.hpp"

class QWidget;

#if defined TEST
#define TEST_COMMON_DLLSPEC  Q_DECL_EXPORT
#else
#define TEST_COMMON_DLLSPEC Q_DECL_IMPORT
#endif

class Shape : public QObject
{
	Q_OBJECT
public:
	Shape();
	virtual ~Shape();
	// This draw() method just rotates painter and then calls _draw() where all things are done
	virtual void draw(QPainter &painter);
	virtual QString getName() = 0;

	virtual QWidget* createControlWidget(QWidget *parent = 0) = 0;

	void rotate(qreal angle);
	void setPos(const QPointF &pos);
	void shift(const QPointF delta_pos);
	void scale(qreal scalex, qreal scaley);
	const QPointF& getPos();

public slots:
	void setX(double x);
	void setY(double y);
	void setScaleX(double scalex);
	void setScaleY(double scaley);
	void visibilityStateChanged(int state);
	void setAngle(int val);

signals:
	void hide();
	void show();

protected:

	QWidget* callUp(QWidget *parent = 0);
	typedef QWidget* (Shape::*ShapeControl)(QWidget *parent);

	virtual QWidget* onCreateControlWidget(QWidget *parent = 0);
	virtual void mydraw(QPainter &painter) = 0;

	qreal m_angle;
	QPointF m_pos;
	bool m_is_visible;
	qreal m_scalex, m_scaley;
};

template <typename T>
class ShapeHelper : public T
{
public:
	ShapeHelper();

	virtual QWidget* createControlWidget(QWidget *parent = 0);
protected:
	QWidget* callUp(QWidget *parent = 0);
};

template <typename T>
ShapeHelper<T>::ShapeHelper()
{

}

template <typename T>
QWidget* ShapeHelper<T>::callUp(QWidget *parent)
{
	QWidget *widget = T::callUp(parent);
	QLayout *layout = widget->layout();
	QWidget *twidget = T::onCreateControlWidget(parent);
	if(twidget != nullptr) {
		layout->addWidget(twidget);

		QFrame *frame = new QFrame(widget);
		frame->setFrameShadow(QFrame::Sunken);
		frame->setLineWidth(1);
		frame->setFixedHeight(3);
		frame->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
		frame->setStyleSheet(QString("background-color: #c0c0c0;"));
		layout->addWidget(frame);
	}
	return widget;
}

template <typename T>
QWidget* ShapeHelper<T>::createControlWidget(QWidget *parent)
{
	QWidget *widget = callUp(parent);
	QLayout *layout = widget->layout();
	QWidget *twidget = this->onCreateControlWidget(parent);
	if(twidget != nullptr) {
		layout->addWidget(twidget);
	}
	return widget;
}

extern "C" TEST_COMMON_DLLSPEC void* createShape();

#endif
