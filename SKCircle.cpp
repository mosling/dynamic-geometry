#include <QtCore/qmath.h>
#include <QDebug>
#include "SKCircle.h"

SKCircle::SKCircle(SKFigure *obj1, SKFigure *obj2)
{
    p1 = obj1;
    p2 = obj2;

    p1->addChild(this);
    p2->addChild(this);

    setFlags(ItemIsSelectable);

    setToolTip("Circle");
    updateItem();
    ld = d;
    lr = r;
}

void SKCircle::updateItem()
{
    qDebug() << "==============================";
    QPointF a = p1->scenePos();
    QPointF b = p2->scenePos();

    setPos(a);
    lr = r;
    ld = d;
    r = qSqrt(qPow(a.x()-b.x(),2)+ qPow(a.y()-b.y(), 2));
    d = 2*r;
    qDebug() << "new circle radius " << r << " position " << a;
    prepareGeometryChange();
}

QRectF SKCircle::boundingRect() const
{
    qDebug() << "bounding box circle item r=" << r;
    return QRectF(-r, -r, d, d);
}

void SKCircle::paint(QPainter *painter,
                     const QStyleOptionGraphicsItem *option,
                     QWidget *widget)
{
    (void)option;
    (void)widget;

    qDebug() << "paint circle item r=" << r;
    QBrush brush(Qt::lightGray);
    QPen pen(brush,2,Qt::DashLine);
    painter->setPen(pen);
    painter->drawRect(boundingRect());

    painter->drawEllipse(boundingRect());

    painter->setPen(QPen(QColor(79, 106, 25), 1, Qt::SolidLine,
                         Qt::FlatCap, Qt::MiterJoin));
    painter->setBrush(QColor(122, 163, 39));
    painter->drawPath(shape());

    qDebug() << "paint circle item end";
}

QPainterPath SKCircle::shape() const
{
    qDebug() << "shape circle item";
    QPainterPath path;
    qreal id = d-r/10.0;
    qreal ir = id/2;
    path.addEllipse(-r,-r,d,d);
    path.addEllipse(-ir,-ir,id,id);
    return path;
}
