#include <QDebug>
#include "Point.h"
#include "PointPath.h"

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

    showBoundingRect(painter);

    QBrush brush(Qt::green);
    if (isSelected())
    {
        brush.setColor(Qt::red);
    }

    painter->setBrush(brush);
    painter->setPen(QPen(Qt::blue, 2, Qt::SolidLine));
    painter->drawEllipse(boundingRect());
}

void Point::setRadius(qreal aRadius)
{
    radius = aRadius;
}
