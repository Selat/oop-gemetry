#include <QApplication>
#include <QDir>
#include <QDebug>
#include <QLibrary>

#include "mainwindow.hpp"

typedef void* (*CreateShapePrototype) ();

void loadLibs(MainWindow &window)
{
	QDir curdir;
	QString filename;
	foreach(filename, curdir.entryList()) {
		if(QLibrary::isLibrary(filename)) {
			QLibrary lib(curdir.filePath(filename));
			CreateShapePrototype func = (CreateShapePrototype)lib.resolve("createShape");
			if(func != NULL) {
				qDebug() << "Found function createShape() in: " << filename;
				Shape *shape = static_cast<Shape*>(func());
				window.addFigure(shape);
			}
		}
	}
}

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    MainWindow window;
    loadLibs(window);
    window.show();
    return app.exec();
}
