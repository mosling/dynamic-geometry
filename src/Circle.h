#pragma once

#include "Shape.h"

//! Creates a circle by two points defining the radius of the circle
class Circle : public Shape
{
    Q_OBJECT

public:
    Circle(Shape *obj1, Shape *obj2);

    ShapeType getTypeClass() const override { return CCLASS; }
    ShapeType getType() const override { return CIRCLE; }

    void updateItem() override;

    QRectF boundingRect() const override;
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;

    QPainterPath shape() const override;

    qreal getRadius() const { return radius; }
    QPointF getCenter() const { return centerPoint->scenePos(); }

protected:

    void setRadius(qreal value) { radius = value; diameter = 2.0 * radius; }

private:

    qreal radius;
    qreal diameter;
    Shape *centerPoint, *borderPoint;
};
