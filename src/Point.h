#pragma once

#include <QSet>
#include "Shape.h"

class Point : public Shape
{
public:
    explicit Point();
    ~Point() override = default;

    ShapeType getTypeClass() const override { return PCLASS; }
    ShapeType getType() const override { return POINT; }

    virtual void updateItem() override;

    QRectF boundingRect() const override;
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;
    QPainterPath shape() const override;

    void setRadius(qreal aRadius);

private:
    qreal radius;
};

