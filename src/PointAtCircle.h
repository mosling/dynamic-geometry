#pragma once

#include "Shape.h"

//! create a line defined by two points
class PointAtCircle : public Shape
{
private:
    Q_OBJECT

public:
    ShapeType getTypeClass() const override { return PCLASS; }
    ShapeType getType() const override { return POINT; }

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
