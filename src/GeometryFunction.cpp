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

QVector<QPointF> GeometryFunction::circleIntersection(const Circle &c1, const Circle &c2)
{
    QVector<QPointF> rl;

    QPointF p1 = c1.getCenter();
    QPointF p2 = c2.getCenter();

    qreal r1 = c1.getRadius();
    qreal r2 = c2.getRadius();

    qreal d = distance(p1, p2);

    if (d <= r1 + r2 && d >= std::abs(r2 - r1))
    {

      qreal ex = (p2.x() - p1.x()) / d;
      qreal ey = (p2.y() - p1.y()) / d;

      qreal x = (r1 * r1 - r2 * r2 + d * d) / (2 * d);
      qreal y = qSqrt(r1 * r1 - x * x);

      QPointF cp1;
      QPointF cp2;

      cp1.setX(p1.x() + x * ex - y * ey);
      cp1.setY(p1.y() + x * ey + y * ex);

      cp2.setX(p1.x() + x * ex + y * ey);
      cp2.setY(p1.y() + x * ey - y * ex);

      rl.append(cp1);
      rl.append(cp2);
    }
    else
    {
        // No Intersection, far outside or one circle within the other
    }

    return rl;
}
