#pragma once


#include "Point.h"

class MidPoint : public Point
{
public:
    ShapeType getTypeClass() const override { return PCLASS; }
    ShapeType getType() const override { return MIDPOINT; }

    MidPoint(Shape *obj1, Shape *obj2);
    ~MidPoint() override = default;

    virtual void updateItem() override;

    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;

private:
    Shape *p1, *p2;
};
