#ifndef GRAPHICSPOINTITEM_H
#define GRAPHICSPOINTITEM_H

#include <QSet>
#include "SKFigure.h"


class SKPoint : public SKFigure
{
public:
    explicit SKPoint();
    ~SKPoint() override = default;

    virtual NsFigure::objEnum getTypeClass() override {return NsFigure::PCLASS; }
    virtual NsFigure::objEnum getType() override {return NsFigure::POINT; }

    QRectF boundingRect() const override;
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;

    void setRadius(qreal aRadius);

private:
    qreal radius;

};

#endif // QGRAPHICSPOINTITEM_H
