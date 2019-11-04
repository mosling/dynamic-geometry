#include <QDebug>
#include "Line.h"
#include "GeometryFunction.h"

Line::Line(Shape *obj1, Shape *obj2)
{
    getOption().setPenColor(QColor(79, 106, 25));
    getOption().setBrushColor(QColor(122, 163, 39));
    getOption().setPenWidth(3.0);

    p1 = obj1;
    p2 = obj2;

    p1->addDependentShape(this);
    p2->addDependentShape(this);

    setToolTip("Line");
}

void Line::updateItem()
{
    setVisible(allBaseShapesVisible());

    QPointF a = p1->scenePos();
    QPointF b = p2->scenePos();

    QLineF tmpLine1 = QLineF(a, b);
    QLineF tmpLine2 = QLineF(b, a);
    tmpLine1.setLength(20000.0);
    tmpLine2.setLength(20000.0);

    line = QLineF(tmpLine1.p2(), tmpLine2.p2());

    prepareGeometryChange();
}

QRectF Line::boundingRect() const
{
    return GeometryFunction::getBoundingBox(line);
}

void Line::paint(QPainter *painter,
                   const QStyleOptionGraphicsItem *option,
                   QWidget *widget)
{
    (void)option;
    (void)widget;

    setOptions(painter);
    painter->drawLine(line);
}

QPainterPath Line::shape() const
{
    QPainterPath path;
    path.moveTo(line.p1());
    path.lineTo(line.p2());
    return path;
}
