TEMPLATE = lib
SOURCES += filledcircle.cpp circle.cpp ../../shape.cpp ../../slidercontrol.cpp
HEADERS += filledcircle.hpp circle.hpp ../../shape.hpp ../../slidercontrol.hpp
#DEFINES += TEST
QMAKE_CXXFLAGS += -std=c++11
INCLUDEPATH += ../ ../../
