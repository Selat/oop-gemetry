#include <QPushButton>
#include <QVBoxLayout>
#include <QDebug>
#include <QDoubleSpinBox>
#include <QCheckBox>
#include <QDial>
#include <QFrame>

#include <cmath>

#include "shape.hpp"
#include "slidercontrol.hpp"

Shape::Shape() :
	QObject(),
	m_angle(0.0),
	m_is_visible(true),
	m_scalex(1.0), m_scaley(1.0)
{
	m_shape_controllers.push_back(&Shape::onCreateControlWidget);
}

Shape::~Shape()
{
}

void Shape::draw(QPainter &painter)
{
	if(m_is_visible) {
		painter.save();
		painter.translate(getPos());
		painter.rotate(m_angle / M_PI * 180.0);
		painter.scale(m_scalex, m_scaley);
		mydraw(painter);
		painter.restore();
	}
}

QWidget* Shape::createControlWidget(QWidget *parent)
{
	QWidget* widget = new QWidget;
	connect(this, SIGNAL(hide()), widget, SLOT(hide()));
	connect(this, SIGNAL(show()), widget, SLOT(show()));
	QVBoxLayout *layout = new QVBoxLayout();
	for(auto controller : m_shape_controllers) {
		QWidget *cur_widget = (this->*controller)(parent);
		if(cur_widget != nullptr) {
			layout->addWidget(cur_widget);
			QFrame *frame = new QFrame;
			frame->setFrameShadow(QFrame::Sunken);
			frame->setLineWidth(1);
			frame->setFixedHeight(3);
			frame->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
			frame->setStyleSheet(QString("background-color: #c0c0c0;"));
			layout->addWidget(frame);

		}
	}
	widget->setLayout(layout);
	return widget;
}

void Shape::rotate(qreal angle)
{
	m_angle = angle;
}

void Shape::setPos(const QPointF &pos)
{
}

void Shape::shift(const QPointF delta_pos)
{
}

const QPointF& Shape::getPos()
{
	return m_pos;
}

void Shape::setX(double x)
{
	m_pos.setX(x);
}

void Shape::setY(double y)
{
	m_pos.setY(y);
}

void Shape::setScaleX(double scalex)
{
	m_scalex = scalex;
}

void Shape::setScaleY(double scaley)
{
	m_scaley = scaley;
}

void Shape::visibilityStateChanged(int state)
{
	if(state == Qt::Checked) {
		m_is_visible = true;
	} else {
		m_is_visible = false;
	}
}

void Shape::setAngle(int angle)
{
	angle = -angle;
	angle -= 90;
	angle += 360;
	if(angle < 0) {
		angle += 360;
	}
	m_angle = (angle / 180.0) * M_PI;
}

QWidget* Shape::onCreateControlWidget(QWidget *parent)
{
	qDebug() << "Shape::create!";
	QWidget *widget = new QWidget(parent);
	QVBoxLayout *main_layout = new QVBoxLayout;
	QHBoxLayout *layout1 = new QHBoxLayout;
	SliderControl *x_coord = new SliderControl(widget);
	x_coord->setValue(0.0);
	layout1->addWidget(x_coord);
	SliderControl *y_coord = new SliderControl(widget);
	y_coord->setValue(0.0);
	layout1->addWidget(y_coord);
	main_layout->addLayout(layout1);

	QHBoxLayout *layout2 = new QHBoxLayout;
	SliderControl *scalex = new SliderControl;
	scalex->setMinimum(0.1);
	scalex->setMaximum(5.0);
	scalex->setValue(1.0);
	layout2->addWidget(scalex);
	SliderControl *scaley = new SliderControl;
	scaley->setMinimum(0.1);
	scaley->setMaximum(5.0);
	scaley->setValue(1.0);
	layout2->addWidget(scaley);
	main_layout->addLayout(layout2);

	QHBoxLayout *layout3 = new QHBoxLayout;
	QCheckBox *show_checkbox = new QCheckBox("Show", widget);
	show_checkbox->setCheckState(Qt::Checked);
	layout3->addWidget(show_checkbox, 0, Qt::AlignJustify);
	QDial *angle = new QDial(widget);
	angle->setNotchTarget(10.0);
	angle->setNotchesVisible(true);
	angle->setWrapping(true);
	angle->setMaximum(359);
	angle->setValue(270);
	layout3->addWidget(angle, 0, Qt::AlignJustify);
	main_layout->addLayout(layout3);
	widget->setLayout(main_layout);

	connect(x_coord, SIGNAL(valueChanged(double)), this, SLOT(setX(double)));
	connect(y_coord, SIGNAL(valueChanged(double)), this, SLOT(setY(double)));
	connect(x_coord, SIGNAL(valueChanged(double)), parent, SLOT(repaint()));
	connect(y_coord, SIGNAL(valueChanged(double)), parent, SLOT(repaint()));
	connect(scalex, SIGNAL(valueChanged(double)), this, SLOT(setScaleX(double)));
	connect(scaley, SIGNAL(valueChanged(double)), this, SLOT(setScaleY(double)));
	connect(scalex, SIGNAL(valueChanged(double)), parent, SLOT(repaint()));
	connect(scaley, SIGNAL(valueChanged(double)), parent, SLOT(repaint()));
	connect(show_checkbox, SIGNAL(stateChanged(int)), this, SLOT(visibilityStateChanged(int)));
	connect(show_checkbox, SIGNAL(stateChanged(int)), parent, SLOT(repaint()));
	connect(angle, SIGNAL(valueChanged(int)), this, SLOT(setAngle(int)));
	connect(angle, SIGNAL(valueChanged(int)), parent, SLOT(repaint()));

	return widget;
}
