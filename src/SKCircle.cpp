#include <QtCore/qmath.h>
#include <QDebug>
#include "SKCircle.h"

SKCircle::SKCircle(SKFigure *obj1, SKFigure *obj2)
{
    p1 = obj1;
    p2 = obj2;

    p1->addBaseFigure(this);
    p2->addBaseFigure(this);

    setFlags(ItemIsSelectable);

    setToolTip("Circle");
    updateItem();
}

void SKCircle::updateItem()
{
    QPointF a = p1->scenePos();
    QPointF b = p2->scenePos();

    setPos(a);
    r = qSqrt(qPow(a.x()-b.x(),2)+ qPow(a.y()-b.y(), 2));
    d = 2*r;

    prepareGeometryChange();
}

QRectF SKCircle::boundingRect() const
{
    return QRectF(-r, -r, d, d);
}

void SKCircle::paint(QPainter *painter,
                     const QStyleOptionGraphicsItem *option,
                     QWidget *widget)
{
    (void)option;
    (void)widget;

    if (withBoundingBox)
    {
        QBrush brush(Qt::lightGray);
        QPen pen(brush,2,Qt::DashLine);
        painter->setPen(pen);
        painter->drawRect(boundingRect());
        painter->drawEllipse(boundingRect());
    }

    painter->setPen(QPen(QColor(79, 106, 25), 1, Qt::SolidLine,
                         Qt::FlatCap, Qt::MiterJoin));
    painter->setBrush(QColor(122, 163, 39));
    painter->drawPath(shape());
}

QPainterPath SKCircle::shape() const
{
    QPainterPath path;
    qreal id = d-r/10.0;
    qreal ir = id/2;
    path.addEllipse(-r,-r,d,d);
    path.addEllipse(-ir,-ir,id,id);
    return path;
}
