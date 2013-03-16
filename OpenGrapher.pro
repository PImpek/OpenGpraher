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
    Gui/graphercanvas.cpp \
    Gui/graphoptions.cpp \
    Gui/axesoptions.cpp \
    actionloader.cpp \
    Modules/csv_import/addcurvedialog.cpp \
    Modules/csv_import/csvimporttool.cpp \
    Gui/GraphiscItems/scaleitem.cpp \
    Gui/GraphiscItems/grapheritem.cpp \
    Gui/GraphiscItems/titleitem.cpp

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
    Gui/graphercanvas.h \
    Interfaces/igraphoptions.h \
    Gui/graphoptions.h \
    Gui/axesoptions.h \
    actionloader.h \
    Interfaces/itool.h \
    Modules/csv_import/addcurvedialog.h \
    Modules/csv_import/csvimporttool.h \
    Gui/GraphiscItems/scaleitem.h \
    Gui/GraphiscItems/grapheritem.h \
    Gui/GraphiscItems/titleitem.h

FORMS    += Ui/mainwindow.ui \
    Ui/curvesmanager.ui \
    Ui/curveproperties.ui \
    Ui/graphoptions.ui \
    Ui/axesoptions.ui \
    Modules/csv_import/addcurvedialog.ui

RESOURCES += \
    resources.qrc

OTHER_FILES += \
    Resources/list-remove.png \
    Resources/list-add.png \
    Resources/go-up.png \
    Resources/go-top.png \
    Resources/go-down.png \
    Resources/format-stroke-color.png \
    Resources/document-save.png \
    Resources/document-save-as.png \
    Resources/document-open.png \
    Resources/document-new.png \
    Resources/application-exit.png \
    Resources/text-csv.png
