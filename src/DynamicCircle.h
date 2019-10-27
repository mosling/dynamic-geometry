#pragma once

#include "Shape.h"

class DynamicCircle : public Shape
{
public:

    const static ShapeType shapeClass = CCLASS;
    const static ShapeType shapeType = DYNCIRCLE;

    DynamicCircle(Shape *obj1, Shape *obj2);

    virtual void updateItem() override;

    QRectF boundingRect() const override;
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;

    QPainterPath shape() const override;

private:
    Shape *p1, *p2;
    qreal radius, diameter;
    // add more private variables
};
