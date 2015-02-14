#include "quadranglediagonals.hpp"

QuadrangleDiagonals::QuadrangleDiagonals()
{
	m_shape_controllers.push_back((ShapeControl)&QuadrangleDiagonals::onCreateControlWidget);
}

QString QuadrangleDiagonals::getName()
{
	return "Quadrangle with diagonals";
}

QWidget* QuadrangleDiagonals::onCreateControlWidget(QWidget *parent)
{
	return nullptr;
}

void QuadrangleDiagonals::mydraw(QPainter &painter)
{
	QPointF points[4];
	QPointF center;
	painter.setPen(Qt::black);
	for(int i = 0; i < 4; ++i) {
		points[i].setX(m_lengths[i] * cos(m_angles[i]));
		points[i].setY(m_lengths[i] * sin(m_angles[i]));
	}
	// Draw outline of the figure
	for(int i = 0; i < 3; ++i) {
		painter.drawLine(points[i], points[i + 1]);
	}
	painter.drawLine(points[0], points[3]);

	// Draw diagonals
	for(int i = 0; i < 4; ++i) {
		painter.drawLine(center, points[i]);
	}
}
