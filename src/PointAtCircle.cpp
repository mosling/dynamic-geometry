#include <QtCore/qmath.h>
#include <QDebug>
#include "GeometryFunction.h"
#include "PointAtCircle.h"

PointAtCircle::PointAtCircle(Shape *obj1, Shape *obj2)
{
    getOption().setPenColor(QColor(79, 106, 25));
    getOption().setBrushColor(QColor(122, 163, 39));

    p1 = obj1;
    p2 = obj2;

    radius = GeometryFunction::distance(p1->scenePos(), p2->scenePos());

    p1->addDependentShape(this);
    p2->addDependentShape(this);

    setToolTip("DistancePoint");
    updateItem();
}

void PointAtCircle::updateItem()
{
    QPointF a = p1->scenePos();
    QPointF b = p2->scenePos();

    radiusLine = QLineF(a, b);
    radiusLine.setLength(radius);

    p2->setPos(radiusLine.p2());

    prepareGeometryChange();
}

QRectF PointAtCircle::boundingRect() const
{
    return GeometryFunction::getBoundingBox(radiusLine);
}

void PointAtCircle::paint(QPainter *painter,
                          const QStyleOptionGraphicsItem *option,
                          QWidget *widget)
{
    (void)option;
    (void)widget;

    showBoundingRect(painter);
    setOptions(painter);
    painter->drawLine(radiusLine);
}

QPainterPath PointAtCircle::shape() const
{

    QPainterPath path;
    path.moveTo(radiusLine.p1());
    path.lineTo(radiusLine.p2());
    return path;
}
