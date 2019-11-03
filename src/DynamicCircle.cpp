#include <QtCore/qmath.h>
#include <QDebug>
#include "GeometryFunction.h"
#include "Circle.h"
#include "DynamicCircle.h"

DynamicCircle::DynamicCircle(Shape *obj1, Shape *obj2)
    : Circle (obj1, obj2)
{
    p1 = obj1;
    p2 = obj2;

    p1->addDependentShape(this);
    p2->addDependentShape(this);

    setToolTip("DynamicCircle");
    updateItem();
}

void DynamicCircle::updateItem()
{
    QPointF a = p1->scenePos();

    setPos(a);
    setRadius((dynamic_cast<Circle *>(p2))->getRadius());

    prepareGeometryChange();
}
