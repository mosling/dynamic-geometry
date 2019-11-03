#include "Segment.h"
#include "GeometryFunction.h"

Segment::Segment(Shape *obj1, Shape *obj2)
{
    getOption().setPenColor(QColor(79, 106, 25));
    getOption().setBrushColor(QColor(122, 163, 39));
    getOption().setPenWidth(3.0);

    p1 = obj1;
    p2 = obj2;

    p1->addDependentShape(this);
    p2->addDependentShape(this);

    setToolTip("Segment");
    updateItem();
}

void Segment::updateItem()
{
    line = QLineF(p1->scenePos(), p2->scenePos());

    prepareGeometryChange();
}

QRectF Segment::boundingRect() const
{
    return GeometryFunction::getBoundingBox(line);
}

void Segment::paint(QPainter *painter,
                   const QStyleOptionGraphicsItem *option,
                   QWidget *widget)
{
    (void)option;
    (void)widget;

    setOptions(painter);
    painter->drawLine(line);
}

QPainterPath Segment::shape() const
{
    QPainterPath path;
    path.moveTo(line.p1());
    path.lineTo(line.p2());
    return path;
}
