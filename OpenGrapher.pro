#-------------------------------------------------
#
# Project created by QtCreator 2013-02-09T13:17:01
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = OpenGrapher
TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++11

SOURCES += main.cpp\
        Gui/mainwindow.cpp \
    servicesprovider.cpp \
    Data/project.cpp \
    Data/curve.cpp \
    Data/graphopts.cpp \
    projectmanager.cpp \
    Gui/curvesmanager.cpp \
    Gui/curveproperties.cpp \
    Gui/graphercanvas.cpp

HEADERS  += Gui/mainwindow.h \
    Interfaces/imainwindow.h \
    servicesprovider.h \
    Interfaces/iservice.h \
    version.h \
    Data/project.h \
    Data/curve.h \
    Data/graphopts.h \
    Interfaces/iprojectmanager.h \
    projectmanager.h \
    Gui/curvesmanager.h \
    Interfaces/icurvesmanager.h \
    Gui/curveproperties.h \
    Interfaces/icurveproperties.h \
    Interfaces/igraphercanvas.h \
    Gui/graphercanvas.h

FORMS    += Ui/mainwindow.ui \
    Ui/curvesmanager.ui \
    Ui/curveproperties.ui
