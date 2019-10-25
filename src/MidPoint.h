#pragma once


#include "Point.h"

class MidPoint : public Point
{
public:
    MidPoint(Shape *obj1, Shape *obj2);
    ~MidPoint() override = default;

    ShapeType getTypeClass() const override { return PCLASS; }
    ShapeType getType() const override { return MIDPOINT; }

    virtual void updateItem() override;

    QRectF boundingRect() const override;
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;
    QPainterPath shape() const override;

private:
    Shape *p1, *p2;
    qreal w, h;
    QPointF l1, l2;
};
