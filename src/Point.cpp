#include <QDebug>
#include "Point.h"

Point::Point()
    : Shape(),
      radius(8)
{
    setToolTip("Point2D");
}

void Point::updateItem()
{
    // nothing to do for points
}

QRectF Point::boundingRect() const
{
    return QRectF(-radius, -radius, 2 * radius, 2 * radius);
}

void Point::paint(QPainter *painter,
                  const QStyleOptionGraphicsItem *option,
                  QWidget *widget)
{
    (void)option;
    (void)widget;

    QRectF rec = boundingRect();
    QBrush brush(Qt::blue);
    QPen pen(brush, 2, Qt::SolidLine);

    if (isSelected())
    {
        brush.setColor(Qt::red);
    }
    else
    {
        brush.setColor(Qt::green);
    }

    painter->setBrush(brush);
    painter->setPen(pen);
    painter->drawEllipse(rec);

    if (getWithBoundingBox())
    {
        QBrush b(Qt::lightGray);
        QPen p(b, 2, Qt::DashLine);
        painter->setPen(p);
        painter->drawRect(boundingRect());
    }
}

void Point::setRadius(qreal aRadius)
{
    radius = aRadius;
}
