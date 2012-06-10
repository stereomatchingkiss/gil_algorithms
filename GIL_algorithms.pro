#-------------------------------------------------
#
# Project created by QtCreator 2012-06-05T13:51:51
#
#-------------------------------------------------

QT       += core gui
CONFIG   += console

TARGET = GIL_algorithms
TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++0x

INCLUDEPATH += ../../boost_minGW/boost_1_49_0
INCLUDEPATH += ../GIL_with_Qt_adapter
INCLUDEPATH += ../Qt_simple_gui


SOURCES += main.cpp

HEADERS  += \
    core_functor.hpp \
    core.hpp \
    gil_core_unit_test.hpp \
    param_type.hpp \
    gil_show_view.hpp
