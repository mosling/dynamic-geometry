#include "SKLine.h"

SKLine::SKLine(SKFigure *obj1, SKFigure *obj2)
{
    p1 = obj1;
    p2 = obj2;

    p1->addBaseFigure(this);
    p2->addBaseFigure(this);

    setFlags(ItemIsSelectable);

    setToolTip("Line");
    updateItem();
}

void SKLine::updateItem()
{
    QPointF a = p1->scenePos();
    QPointF b = p2->scenePos();

    QLineF tmpLine1 = QLineF (a,b);
    QLineF tmpLine2 = QLineF (b,a);
    tmpLine1.setLength(20000.0);
    tmpLine2.setLength(20000.0);

    line = QLineF(tmpLine1.p2(), tmpLine2.p2());

    prepareGeometryChange();
}

QRectF SKLine::boundingRect() const
{
    qreal left = std::min(line.x1(), line.x2());
    qreal top = std::min(line.y1(), line.y2());
    qreal width = std::abs((line.x1()-line.x2()));
    qreal height = std::abs((line.y1()-line.y2()));

    return QRectF(left, top, width, height);
}

void SKLine::paint(QPainter *painter,
                   const QStyleOptionGraphicsItem *option,
                   QWidget *widget)
{
    (void)option;
    (void)widget;

    painter->setPen(QPen(QColor(79, 106, 25), 3, Qt::SolidLine,
                         Qt::FlatCap, Qt::MiterJoin));
    painter->setBrush(QColor(122, 163, 39));
    painter->drawLine(line);
}

QPainterPath SKLine::shape() const
{
    QPainterPath path;
    path.moveTo(line.p1());
    path.lineTo(line.p2());
    return path;
}

