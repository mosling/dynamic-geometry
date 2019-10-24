#ifndef SKCIRCLE_H
#define SKCIRCLE_H

#include "SKFigure.h"

//! Kreis bestehend aus einem Mittelpunkt und einem Punkt auf dem Rand
class SKCircle : public SKFigure
{
public:
    SKCircle(SKFigure *obj1, SKFigure *obj2);

    virtual NsFigure::objEnum getTypeClass() override { return NsFigure::CCLASS; }
    virtual NsFigure::objEnum getType() override { return NsFigure::CIRCLE; }
    virtual void updateItem() override;

    QRectF boundingRect() const override;
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;
    QPainterPath shape() const override;

private:
    SKFigure *p1, *p2;
    qreal    lr, r;
    qreal    ld, d;
    bool     lastBox;
};

#endif // SKCIRCLE_H
