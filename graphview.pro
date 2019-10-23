#-------------------------------------------------
#
# Project created by QtCreator 2011-07-11T22:08:36
#
#-------------------------------------------------

QT       += core gui widgets

TARGET = graphview
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    GraphicsSelectionScene.cpp \
    SKFigure.cpp \
    SKPoint.cpp \
    SKMidPoint.cpp \
    SKCircle.cpp

HEADERS  += mainwindow.h \
    GraphicsSelectionScene.h \
    SKFigure.h \
    SKPoint.h \
    FigureTypes.h \
    AllFigures.h \
    SKMidPoint.h \
    SKCircle.h

FORMS    += mainwindow.ui

RESOURCES += \
    graphview.qrc
