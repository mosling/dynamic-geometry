#pragma once

#include "Shape.h"

//! Creates a circle by two points defining the radius of the circle
class Circle : public Shape
{
public:
    Circle(Shape *obj1, Shape *obj2);

    ShapeType getTypeClass() const override { return CCLASS; }
    ShapeType getType() const override { return CIRCLE; }

    virtual void updateItem() override;

    qreal inline getRadius() { return radius; }
    QRectF boundingRect() const override;
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;

    QPainterPath shape() const override;

private:
    qreal radius, diameter;
    bool lastBox;
    Shape *p1, *p2;
};
