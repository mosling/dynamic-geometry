#include <QDebug>
#include "MidPoint.h"

MidPoint::MidPoint(Shape *obj1, Shape *obj2)
    : Point()
{
    p1 = obj1;
    p2 = obj2;

    p1->addDependentShape(this);
    p2->addDependentShape(this);

    setFlags(ItemIsSelectable);

    setToolTip("MidPoint");
    updateItem();
}

void MidPoint::updateItem()
{
    QPointF a = p1->scenePos();
    QPointF b = p2->scenePos();
    bool nw = false;
    bool nh = false;

    w = qAbs(a.x() - b.x());
    h = qAbs(a.y() - b.y());
    nw = w < 10;
    nh = h < 10;

    l1.setX(-w / 2);
    l2.setX(w / 2);
    if (a.x() < b.x())
    {
        l1.setY(a.y() > b.y() ? h / 2 : -h / 2);
        l2.setY(a.y() > b.y() ? -h / 2 : h / 2);
    }
    else
    {
        l1.setY(b.y() > a.y() ? h / 2 : -h / 2);
        l2.setY(b.y() > a.y() ? -h / 2 : h / 2);
    }

    setPos(a.x() + (b.x() - a.x()) / 2.0, a.y() + (b.y() - a.y()) / 2.0);

    // todo: what is the sense of the following lines
    if (nw)
        w = 10.0;
    if (nh)
        h = 10.0;
}

QRectF MidPoint::boundingRect() const
{
    return QRectF(-w / 2, -h / 2, w, h);
}

void MidPoint::paint(QPainter *painter,
                       const QStyleOptionGraphicsItem *option,
                       QWidget *widget)
{
    (void)option;
    (void)widget;

    QPen penP(Qt::blue);

    if (getWithBoundingBox())
    {
        QBrush brush(Qt::lightGray);
        QPen pen(brush, 2, Qt::DashLine);
        painter->setPen(pen);
        painter->drawRect(boundingRect());
    }

    painter->setBrush(QBrush(Qt::yellow));
    painter->setPen(penP);
    painter->drawLine(l1, l2);
    painter->drawEllipse(-5, -5, 10, 10);
}

QPainterPath MidPoint::shape() const
{
    QPainterPath path;
    path.addEllipse(-5, -5, 10, 10);
    return path;
}
