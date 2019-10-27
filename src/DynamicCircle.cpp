#include <QtCore/qmath.h>
#include <QDebug>
#include "GeometryFunction.h"
#include "Circle.h"
#include "DynamicCircle.h"

DynamicCircle::DynamicCircle(Shape *obj1, Shape *obj2)
{
    p1 = obj1;
    p2 = obj2;

    p1->addDependentShape(this);
    p2->addDependentShape(this);

    setFlags(ItemIsSelectable);

    setToolTip("DynamicCircle");
    updateItem();
}

void DynamicCircle::updateItem()
{
    QPointF a = p1->scenePos();

    setPos(a);
    radius = (dynamic_cast<Circle *>(p2))->getRadius();
    diameter = 2 * radius;

    prepareGeometryChange();
}

QRectF DynamicCircle::boundingRect() const
{
    return QRectF(-radius, -radius, diameter, diameter);
}

void DynamicCircle::paint(QPainter *painter,
                   const QStyleOptionGraphicsItem *option,
                   QWidget *widget)
{
    (void)option;
    (void)widget;

    if (getWithBoundingBox())
    {
        QBrush brush(Qt::lightGray);
        QPen pen(brush, 2, Qt::DashLine);
        painter->setPen(pen);
        painter->drawRect(boundingRect());
        painter->drawEllipse(boundingRect());
    }

    painter->setPen(QPen(QColor(79, 106, 25), 1, Qt::SolidLine,
                         Qt::FlatCap, Qt::MiterJoin));
    painter->setBrush(QColor(122, 163, 39));
    painter->drawPath(shape());
}

QPainterPath DynamicCircle::shape() const
{
    QPainterPath path;
    qreal id = diameter - 2.0;
    qreal ir = id / 2.0;
    path.addEllipse(-radius, -radius, diameter, diameter);
    path.addEllipse(-ir, -ir, id, id);
    return path;
}
