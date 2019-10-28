QMAKE_CXXFLAGS += -Wno-padded

INCLUDEPATH    += src/
RESOURCES      += resources/icons.qrc

TEMPLATE        = subdirs
CONFIG         += ordered

SUBDIRS         = src
