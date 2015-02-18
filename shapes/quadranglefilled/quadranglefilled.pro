TEMPLATE = lib
SOURCES += quadranglefilled.cpp quadranglediagonals.cpp quadrangle.cpp ../../shape.cpp ../../slidercontrol.cpp
HEADERS += quadranglefilled.hpp quadranglediagonals.hpp quadrangle.hpp ../../shape.hpp ../../slidercontrol.hpp
#DEFINES += TEST
QMAKE_CXXFLAGS += -std=c++11
INCLUDEPATH += ../ ../../
