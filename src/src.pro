CONFIG         += c++17
QT             += core gui widgets

TARGET         = dynamic-geometry
TEMPLATE       = app


SOURCES += \
    Circle.cpp \
    GeometryFunction.cpp \
    GeometryView.cpp \
    main.cpp \
    MidPoint.cpp \
    PointAtCircle.cpp \
    DynamicCircle.cpp \
    GeometryScene.cpp \
    Line.cpp \
    mainwindow.cpp \
    Point.cpp \
    Shape.cpp

HEADERS += \
    Circle.h \
    GeometryFunction.h \
    GeometryView.h \
    MidPoint.h \
    PointAtCircle.h \
    DynamicCircle.h \
    GeometryScene.h \
    Line.h \
    mainwindow.h \
    Point.h \
    Shape.h

FORMS += mainwindow.ui

OTHER_FILES += \
    Shape.h.template \
    Shape.cpp.template
