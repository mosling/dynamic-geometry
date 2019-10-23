#ifndef SKCIRCLE_H
#define SKCIRCLE_H

#include "SKFigure.h"

//! Kreis bestehend aus einem Mittelpunkt und einem Punkt auf dem Rand
class SKCircle : public SKFigure
{
public:
    SKCircle(SKFigure *obj1, SKFigure *obj2);

    virtual NsFigure::objEnum getType();
    virtual NsFigure::objEnum getTypeClass();
    virtual void updateItem();

    QRectF boundingRect() const;
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget);
    QPainterPath shape() const;


private:
    SKFigure *p1, *p2;
    qreal lr, r;
    qreal ld, d;
    bool lastBox;
};

#endif // SKCIRCLE_H
