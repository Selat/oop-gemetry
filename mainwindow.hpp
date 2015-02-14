#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QVector>
#include <QPair>

#include "canvas.hpp"

class QStackedLayout;
class QListWidget;

class Shape;

class MainWindow : public QMainWindow
{
	Q_OBJECT
public:
    MainWindow();
	void addFigure(Shape *shape);

public slots:
	void currentFigureChanged(int id);

private:

	Canvas *m_canvas;
	QWidget *m_window;
	QStackedLayout *m_control_layout;
	QListWidget *m_figures_list;

	QVector <QPair <Shape*, int> > m_figures;
	int m_cur_figure;
};


#endif // MainWindow_H
