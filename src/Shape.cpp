#include <QDebug>
#include "Shape.h"

const QList<QString> Shape::typeName = {"class-of-texts", "class-of-lines",
                                        "class-of-points", "class-of-circles", "object",
                                        "multifig", "point", "segment", "line", "ray", "circle", "text",
                                        "circle-intersection", "intersection-point", "middle-point",
                                        "point-on-line", "mirror-point", "distance-point", "middle-line",
                                        "plumb-line", "parallel-line", "horizontal-line", "algorithm",
                                        "dyn-circle", "path-of-points"};

const QList<QChar> Shape::typeShortname = {'T', 'L', 'P', 'C', 'O', 'M', 'p', 's',
                                           'l', 'r', 'c', 't', '_', 'i', '_', '_', '_', 'd', '_',
                                           '_', '_', 'h', 'a', '_', '_' };

Shape::Shape()
    : QGraphicsItem(),
      m_boundingBox(false),
      m_helper(false)
{
    Q_ASSERT(STOPPER == typeName.length() );
    Q_ASSERT(STOPPER == typeShortname.length() );

    setFlag(ItemIsMovable, false); // points movable only !!
    setFlag(ItemIsSelectable, true);
    setFlag(ItemSendsGeometryChanges, true);

    setToolTip("BaseFigure");
}

Shape::~Shape()
{
    Q_FOREACH (Shape *p, baseShapeSet)
    {
        p->removeDependentShape(this);
    }

    Q_FOREACH (Shape *c, dependentShapeSet)
    {
        delete c;
    }

    dependentShapeSet.clear();
    baseShapeSet.clear();
}

bool Shape::allBaseShapesVisible()
{
    bool v = true;
    Q_FOREACH (Shape *shape, baseShapeSet)
    {
        v = v && shape->isVisible();
    }

    return v;
}

void Shape::showBoundingRect(QPainter *painter)
{
    if (boundingBox())
    {
        QBrush brush(Qt::lightGray);
        QPen pen(brush, 2, Qt::DashLine);
        painter->setPen(pen);
        painter->drawRect(boundingRect());
    }
}

void Shape::setOptions(QPainter *painter)
{
    QColor pcol = helper() ? Qt::lightGray : (isSelected() ? getOption().selectedColor() : getOption().penColor());
    QColor bcol = helper() ? Qt::lightGray : (isSelected() ? getOption().selectedColor() : getOption().brushColor());
    qreal lw = helper() ? 1.0 : getOption().penWidth();

    painter->setBrush(QBrush(bcol));
    painter->setPen(QPen(pcol, lw, getOption().penStyle(), Qt::FlatCap, Qt::MiterJoin));

    painter->setRenderHint(QPainter::Antialiasing, true);
    painter->setRenderHint(QPainter::SmoothPixmapTransform, true);
}

void Shape::addDependentShape(Shape *child)
{
    dependentShapeSet.append(child);
    child->baseShapeSet.append(this);
}

void Shape::removeDependentShape(Shape *child)
{
    if (child != this)
    {
        dependentShapeSet.removeOne(child);
    }
}

QVariant Shape::itemChange(QGraphicsItem::GraphicsItemChange change,
                           const QVariant &value)
{
    if (change == ItemPositionHasChanged && scene())
    {
        Q_FOREACH (Shape *shape, dependentShapeSet)
        {
            shape->updateItem();
            shape->itemChange(change, value);
        }
    }

    return QGraphicsItem::itemChange(change, value);
}
