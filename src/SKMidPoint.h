#ifndef MIDPOINT_H
#define MIDPOINT_H

#include "SKPoint.h"

class SKMidPoint : public SKPoint
{
public:
    SKMidPoint(SKFigure *obj1, SKFigure *obj2);
    ~SKMidPoint() override = default;

    virtual NsFigure::objEnum getTypeClass() override { return NsFigure::PCLASS; }
    virtual NsFigure::objEnum getType() override { return NsFigure::MIDPOINT; }
    virtual void updateItem() override;

    QRectF boundingRect() const override;
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;
    QPainterPath shape() const override;

private:
    SKFigure *p1, *p2;
    qreal    w, h;
    QPointF  l1, l2;
};

#endif // MIDPOINT_H
