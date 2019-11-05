#pragma once

#include "Circle.h"
#include "Point.h"

//! create a line defined by two points
class CircleIntersection : public Shape
{
private:
    Q_OBJECT

public:
    const static ShapeType shapeClass = POINT;
    const static ShapeType shapeType = CIRCINT;

    CircleIntersection(Shape *obj1, Shape *obj2);

    virtual void updateItem() override;

    QRectF boundingRect() const override;
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;

private:
    Circle *c1, *c2;
    Point *ip[2];
};
