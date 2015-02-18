TEMPLATE = lib
SOURCES += quadranglediagonals.cpp quadrangle.cpp ../../shape.cpp ../../slidercontrol.cpp
HEADERS += quadranglediagonals.hpp quadrangle.hpp ../../shape.hpp ../../slidercontrol.hpp
#DEFINES += TEST
QMAKE_CXXFLAGS += -std=c++11
INCLUDEPATH += ../ ../../
