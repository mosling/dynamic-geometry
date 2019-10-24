#ifndef SKCIRCLE_H
#define SKCIRCLE_H

#include "SKFigure.h"

//! Creates a circle by two points defining the radius of the circle
class SKCircle : public SKFigure
{
public:
    SKCircle(SKFigure *obj1, SKFigure *obj2);

    virtual NsFigure::objEnum getTypeClass() override
    {
        return NsFigure::CCLASS;
    }
    virtual NsFigure::objEnum getType() override
    {
        return NsFigure::CIRCLE;
    }
    virtual void updateItem() override;

    QRectF boundingRect() const override;
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;
    QPainterPath shape() const override;

private:
    qreal    r, d;
    bool     lastBox;
    SKFigure *p1, *p2;
};

#endif // SKCIRCLE_H
