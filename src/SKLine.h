#ifndef SKLINE_H
#define SKLINE_H

#include "SKFigure.h"

//! create a line defined by two points
class SKLine : public SKFigure
{

public:
    SKLine(SKFigure *obj1, SKFigure *obj2);

    virtual NsFigure::objEnum getTypeClass() override
    {
        return NsFigure::LCLASS;
    }
    virtual NsFigure::objEnum getType() override
    {
        return NsFigure::LINE;
    }
    virtual void updateItem() override;

    QRectF boundingRect() const override;
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;
    QPainterPath shape() const override;

private:
    SKFigure *p1, *p2;
    QLineF line;

};

#endif // SKLINE_H
