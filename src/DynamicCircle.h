#pragma once

#include "Shape.h"

class DynamicCircle : public Circle
{
public:

    const static ShapeType shapeClass = CCLASS;
    const static ShapeType shapeType = DYNCIRCLE;

    DynamicCircle(Shape *obj1, Shape *obj2);

    virtual void updateItem() override;

private:
    Shape *p1, *p2;
};
