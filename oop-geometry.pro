QT += widgets
QMAKE_CXXFLAGS += -std=c++11

SOURCES += \
	main.cpp \
	mainwindow.cpp \
    canvas.cpp \
    slidercontrol.cpp \
    shape/shape.cpp \
    shape/circle.cpp \
    shape/filledcircle.cpp \
    shape/quadrangle.cpp \
    shape/quadranglediagonals.cpp \
    shape/quadranglefilled.cpp

HEADERS += \
	mainwindow.hpp \
    canvas.hpp \
    slidercontrol.hpp \
    shape/shape.hpp \
    shape/circle.hpp \
    shape/filledcircle.hpp \
    shape/quadrangle.hpp \
    shape/quadranglediagonals.hpp \
    shape/quadranglefilled.hpp
