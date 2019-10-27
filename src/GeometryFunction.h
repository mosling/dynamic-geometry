#pragma once

#include <QPointF>
#include <QRectF>
#include <QLineF>

class GeometryFunction
{
public:
    static qreal distance (const QPointF &p1, const QPointF &p2);
    static QRectF getBoundingBox(const QPointF &p1, const QPointF &p2);
    static inline QRectF getBoundingBox(const QLineF &l) { return getBoundingBox(l.p1(), l.p2()); }
};
