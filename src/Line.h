#pragma once

#include "Shape.h"

//! create a line defined by two points
class Line : public Shape
{
private:
    Q_OBJECT

public:
    const static ShapeType shapeClass = LCLASS;
    const static ShapeType shapeType = LINE;

    Line(Shape *obj1, Shape *obj2);

    virtual void updateItem() override;

    QRectF boundingRect() const override;
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;

    QPainterPath shape() const override;

private:
    Shape *p1, *p2;
    QLineF line;
};
