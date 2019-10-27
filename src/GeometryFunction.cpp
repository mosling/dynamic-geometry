#include <QtMath>
#include "GeometryFunction.h"

qreal GeometryFunction::distance(const QPointF &p1, const QPointF &p2)
{
    return qSqrt(qPow(p1.x() - p2.x(), 2) + qPow(p1.y() - p2.y(), 2));
}

QRectF GeometryFunction::getBoundingBox(const QPointF &p1, const QPointF &p2)
{
    qreal left   = std::min(p1.x(), p2.x());
    qreal top    = std::min(p1.y(), p2.y());
    qreal width  = std::abs((p1.x() - p2.x()));
    qreal height = std::abs((p1.y() - p2.y()));

    return QRectF(left, top, width, height);
}
