#include <QtCore/qmath.h>
#include <QDebug>
#include "GeometryFunction.h"
#include "Circle.h"

Circle::Circle(Shape *obj1, Shape *obj2)
{
    p1 = obj1;
    p2 = obj2;

    p1->addDependentShape(this);
    p2->addDependentShape(this);

    setFlags(ItemIsSelectable);

    setToolTip("Circle");
    updateItem();
}

void Circle::updateItem()
{
    QPointF a = p1->scenePos();
    QPointF b = p2->scenePos();

    setPos(a);
    radius = GeometryFunction::distance(a, b);
    diameter = 2 * radius;

    prepareGeometryChange();
}

QRectF Circle::boundingRect() const
{
    return QRectF(-radius, -radius, diameter, diameter);
}

void Circle::paint(QPainter *painter,
                   const QStyleOptionGraphicsItem *option,
                   QWidget *widget)
{
    (void)option;
    (void)widget;

    showBoundingRect(painter);

    if (isConstructionHelper())
    {
        painter->setPen(QPen(Qt::darkCyan, 1, Qt::SolidLine,
                             Qt::FlatCap, Qt::MiterJoin));
        painter->setBrush(Qt::cyan);
    }
    else
    {
        painter->setPen(QPen(getConstructionColor(), 1, Qt::SolidLine,
                             Qt::FlatCap, Qt::MiterJoin));
        painter->setBrush(getConstructionColor());
    }

    painter->setRenderHint(QPainter::Antialiasing, true);
    painter->setRenderHint(QPainter::SmoothPixmapTransform, true);
    painter->drawPath(shape());
}

QPainterPath Circle::shape() const
{
    QPainterPath path;
    qreal id = diameter - 4.0;
    qreal ir = id / 2.0;
    path.addEllipse(-radius, -radius, diameter, diameter);
    path.addEllipse(-ir, -ir, id, id);
    return path;
}
