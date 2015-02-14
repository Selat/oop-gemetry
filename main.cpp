#include <QApplication>

#include "shape/circle.hpp"
#include "shape/filledcircle.hpp"
#include "shape/quadrangle.hpp"
#include "mainwindow.hpp"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    MainWindow window;
    Circle *circle = new Circle();
    window.addFigure(circle);
    FilledCircle *filledcircle = new FilledCircle();
    window.addFigure(filledcircle);
    Quadrangle *quadrangle = new Quadrangle();
    window.addFigure(quadrangle);
    window.show();
    return app.exec();
}
