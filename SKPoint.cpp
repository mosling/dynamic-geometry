﻿#include <QDebug>
#include "SKPoint.h"

SKPoint::SKPoint() :	SKFigure(), radius(5)
{
    setToolTip("Point2D");
}

SKPoint::~SKPoint()
{

}

NsFigure::objEnum SKPoint::getType()
{
    return NsFigure::POINT;
}

NsFigure::objEnum SKPoint::getTypeClass()
{
    return NsFigure::PCLASS;
}

QRectF SKPoint::boundingRect() const
{
    return QRectF(-radius, -radius, 2*radius, 2*radius);
}

void SKPoint::paint(QPainter *painter,
                    const QStyleOptionGraphicsItem *option,
                    QWidget *widget)
{
    QRectF rec = boundingRect();
    QBrush brush(Qt::blue);
    QPen pen(brush,2,Qt::SolidLine);

    if (isSelected()) brush.setColor(Qt::red);
    else brush.setColor(Qt::green);

    painter->setBrush(brush);
    painter->setPen(pen);
    painter->drawEllipse(rec);

    QBrush b(Qt::lightGray);
    QPen p(b,2,Qt::DashLine);
    painter->setPen(p);
    painter->drawRect(boundingRect());
}

void SKPoint::setRadius(qreal aRadius)
{
    radius = aRadius;
}


