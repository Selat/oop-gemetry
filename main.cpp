#include <QApplication>

#include "shape/circle.hpp"
#include "shape/filledcircle.hpp"
#include "shape/quadrangle.hpp"
#include "shape/quadranglediagonals.hpp"
#include "shape/quadranglefilled.hpp"
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
    QuadrangleDiagonals *quadranglediagonals = new QuadrangleDiagonals();
    window.addFigure(quadranglediagonals);
    QuadrangleFilled *quadranglefilled = new QuadrangleFilled();
    window.addFigure(quadranglefilled);
    window.show();
    return app.exec();
}
