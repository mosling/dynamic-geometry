#pragma once

#include "Shape.h"

class PointPath : public Shape
{

public:
    const static ShapeType shapeClass = OBJECT;
    const static ShapeType shapeType = POINTPATH;

    PointPath(Shape *obj1);

    virtual void updateItem() override;
    void cleanTracker();

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

