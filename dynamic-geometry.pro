CONFIG         += c++17
QT             += core gui widgets

TARGET         = dynamic-geometry
TEMPLATE       = app


SOURCES        += $$files(src/*.cpp, true)
HEADERS        += $$files(src/*.h, true)

INCLUDEPATH    *= src/
FORMS          += ui/mainwindow.ui

RESOURCES      += resources/icons.qrc

DISTFILES += \
    src/Shape.h.template
