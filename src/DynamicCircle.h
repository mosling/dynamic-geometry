#pragma once

#include "Circle.h"

class DynamicCircle : public Circle
{
private:
    Q_OBJECT

public:

    DynamicCircle(Shape *obj1, Shape *obj2);

    ShapeType getTypeClass() const override { return CCLASS; }
    ShapeType getType() const override { return DYNCIRCLE; }

    virtual void updateItem() override;

private:
    Shape *p1, *p2;
};
