#ifndef SHAPE_HPP
#define SHAPE_HPP

#include <QtGlobal>
#include <QPainter>
#include <QPointF>
#include <QString>

class QWidget;

class Shape : public QObject
{
	Q_OBJECT
public:
	Shape();
	virtual ~Shape();
	// This draw() method just rotates painter and then calls _draw() where all things are done
	virtual void draw(QPainter &painter);
	virtual QString getName() = 0;

	QWidget* createControlWidget(QWidget *parent = 0);

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
	typedef QWidget* (Shape::*ShapeControl)(QWidget *parent);

	QWidget* onCreateControlWidget(QWidget *parent = 0);
	virtual void mydraw(QPainter &painter) = 0;

	qreal m_angle;
	QPointF m_pos;
	bool m_is_visible;
	qreal m_scalex, m_scaley;

	QVector <ShapeControl> m_shape_controllers;
};

#endif
