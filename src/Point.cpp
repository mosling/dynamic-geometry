#include <QDebug>
#include "Point.h"
#include "PointPath.h"

Point::Point()
    : Shape(),
      radius(8)
{
    setFlag(ItemIsMovable, true);

    setToolTip("Point2D");
}

void Point::updateItem()
{
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
    setOptions(painter);

    painter->drawEllipse(boundingRect());
}

void Point::setRadius(qreal aRadius)
{
    radius = aRadius;
}

QPainterPath Point::shape() const
{
    QPainterPath path;
    path.addRect(boundingRect());
    return path;
}
