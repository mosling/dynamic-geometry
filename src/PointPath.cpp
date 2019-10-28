#include "PointPath.h"
#include "GeometryFunction.h"

PointPath::PointPath(Shape *obj1)
    : resolution(5.0)
{
    shape1 = obj1;
    shape1->addDependentShape(this);

    pointPath.append(shape1->scenePos());
    setFlags(ItemIsSelectable);

    setToolTip("PointPath");
    updateItem();
}

void PointPath::updateItem()
{
    QPointF p = shape1->scenePos();
    if (GeometryFunction::distance(pointPath.at(pointPath.length() - 1), p) > resolution)
    {
        pointPath.append(p);
    }
    prepareGeometryChange();
}

void PointPath::cleanTracker()
{
    pointPath.clear();
    pointPath.append(shape1->scenePos());
    updateItem();
}

QRectF PointPath::boundingRect() const
{
    return shape().boundingRect();
}

void PointPath::paint(QPainter *painter,
                   const QStyleOptionGraphicsItem *option,
                   QWidget *widget)
{
    (void)option;
    (void)widget;

    // use given painter to draw the object
    painter->setPen(QPen(QColor(79, 106, 25), 3, Qt::SolidLine,
                         Qt::FlatCap, Qt::MiterJoin));
    painter->setBrush(QColor(122, 163, 39));
    painter->setRenderHint(QPainter::Antialiasing, true);
    painter->setRenderHint(QPainter::SmoothPixmapTransform, true);
    QPointF lp;
    bool firstPoint = true;
    foreach (QPointF p, pointPath)
    {
        painter->drawPoint(p);
        if (!firstPoint)
        {
            painter->drawLine(lp,p);
        }
        else
        {
            firstPoint = false;
        }
        lp = p;
    }
}

QPainterPath PointPath::shape() const
{
    QPainterPath path;
    foreach( QPointF p, pointPath)
    {
        path.moveTo(p);
    }
    return path;
}