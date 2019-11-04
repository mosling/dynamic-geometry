#include <QDebug>
#include "MidPoint.h"

MidPoint::MidPoint(Shape *obj1, Shape *obj2)
    : Point()
{
    p1 = obj1;
    p2 = obj2;

    p1->addDependentShape(this);
    p2->addDependentShape(this);

    setToolTip("MidPoint");
    updateItem();
}

void MidPoint::updateItem()
{
    setVisible(allBaseShapesVisible());

    QPointF a = p1->scenePos();
    QPointF b = p2->scenePos();

    setPos(a.x() + (b.x() - a.x()) / 2.0, a.y() + (b.y() - a.y()) / 2.0);
}

void MidPoint::paint(QPainter *painter,
                       const QStyleOptionGraphicsItem *option,
                       QWidget *widget)
{
    (void)option;
    (void)widget;

    showBoundingRect(painter);
    setOptions(painter);

    painter->drawEllipse(boundingRect());
}

