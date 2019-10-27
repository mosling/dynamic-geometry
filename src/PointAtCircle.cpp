#include <QtCore/qmath.h>
#include <QDebug>
#include "GeometryFunction.h"
#include "PointAtCircle.h"

PointAtCircle::PointAtCircle(Shape *obj1, Shape *obj2)
{
    p1 = obj1;
    p2 = obj2;

    radius = GeometryFunction::distance(p1->scenePos(), p2->scenePos());

    p1->addDependentShape(this);
    p2->addDependentShape(this);

    setFlags(ItemIsSelectable);

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

    painter->setPen(QPen(QColor(79, 106, 25), 3, Qt::SolidLine,
                         Qt::FlatCap, Qt::MiterJoin));
    painter->setBrush(QColor(122, 163, 39));
    painter->setRenderHint(QPainter::Antialiasing, true);
    painter->setRenderHint(QPainter::SmoothPixmapTransform, true);
    painter->drawLine(radiusLine);
}

QPainterPath PointAtCircle::shape() const
{

    QPainterPath path;
    path.moveTo(radiusLine.p1());
    path.lineTo(radiusLine.p2());
    return path;
}
