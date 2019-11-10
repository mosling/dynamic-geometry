#include <QtCore/qmath.h>
#include <QDebug>
#include "GeometryFunction.h"
#include "Circle.h"

Circle::Circle(Shape *obj1, Shape *obj2)
    : radius(0),
      diameter(0)
{
    getOption().setPenColor(Qt::darkCyan);
    getOption().setBrushColor(Qt::cyan);

    centerPoint = obj1;
    borderPoint = obj2;

    centerPoint->addDependentShape(this);
    borderPoint->addDependentShape(this);

    setToolTip(QStringLiteral("Circle"));
}

void Circle::updateItem()
{
    setVisible(allBaseShapesVisible());

    setPos(centerPoint->scenePos());
    radius = GeometryFunction::distance(centerPoint->scenePos(), borderPoint->scenePos());
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
    setOptions(painter);

    painter->drawPath(shape());
}

QPainterPath Circle::shape() const
{
    QPainterPath path;
    qreal id = diameter - 6.0;
    qreal ir = id / 2.0;
    path.addEllipse(-radius, -radius, diameter, diameter);
    path.addEllipse(-ir, -ir, id, id);
    return path;
}
