#pragma once

#include "Shape.h"

class PointPath : public Shape
{

public:
    ShapeType getTypeClass() const override { return OBJECT; }
    ShapeType getType() const override { return POINTPATH; }

    PointPath(Shape *obj1);

    virtual void updateItem() override;

    QRectF boundingRect() const override;
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;

    QPainterPath shape() const override;

private:
    Shape *shape1;
    QList<QPointF> pointPath;
    qreal resolution;
};

