#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QStackedLayout>
#include <QListWidget>

#include <QDebug>

#include "shape.hpp"
#include "canvas.hpp"
#include "mainwindow.hpp"

MainWindow::MainWindow()
{
	m_window = new QWidget();

	// At the left side of the window there is a list of all available figures
	m_figures_list = new QListWidget();
	m_figures_list->setMinimumWidth(100);
	m_figures_list->setMaximumWidth(100);
	m_figures_list->setSizePolicy(QSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum));

	// Properties are located at the right part of the window
	m_control_layout = new QStackedLayout();
	m_control_layout->setSizeConstraint(QLayout::SetMinimumSize);

	// At the central part of the screen there is a canvas that displays current figure
	QHBoxLayout *main_layout = new QHBoxLayout(m_window);
	main_layout->addWidget(m_figures_list);
	m_canvas = new Canvas(this);
	m_canvas->show();
	main_layout->addWidget(m_canvas);
	main_layout->addLayout(m_control_layout);
	setCentralWidget(m_window);
	m_window->show();

	connect(m_figures_list, SIGNAL(currentRowChanged(int)), this, SLOT(currentFigureChanged(int)));
}

void MainWindow::currentFigureChanged(int id)
{
	m_control_layout->setCurrentIndex(id);
	m_canvas->setCurrentFigure(m_figures[id].first);
}

void MainWindow::addFigure(Shape *shape)
{
	QWidget *control_widget = shape->createControlWidget(m_canvas);
	int id = m_control_layout->addWidget(control_widget);
	m_figures_list->addItem(shape->getName());
	m_figures.push_back(qMakePair(shape, id));
	// This was the first shape to we set it as current for Canvas
	if(m_figures.size() == 1) {
		m_canvas->setCurrentFigure(shape);
	}
}
