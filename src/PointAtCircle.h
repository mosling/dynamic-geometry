#pragma once

#include "Shape.h"

//! create a line defined by two points
class PointAtCircle : public Shape
{

public:
    const static ShapeType shapeClass = PCLASS;
    const static ShapeType shapeType = POINT;

    PointAtCircle(Shape *obj1, Shape *obj2);

    virtual void updateItem() override;

    QRectF boundingRect() const override;
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;

    QPainterPath shape() const override;

private:
    Shape *p1, *p2;
    qreal radius;
    QLineF radiusLine;

};
