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
                         'l', 'r', 'c', 't', '_', 'i', '_', '_', '_', 'd', '_', '_', '_', 'h',
                         'a', '_', '_' };

Shape::Shape()
    : QGraphicsItem(),
      withBoundingBox(true),
      constructionHelper(true),
      constructionColor(QColor("#f0f0f0"))
{
    Q_ASSERT(STOPPER == typeName.length() );
    Q_ASSERT(STOPPER == typeShortname.length() );

	setFlag(ItemIsMovable);
	setFlag(ItemIsSelectable);
	setFlag(ItemSendsGeometryChanges);

	setToolTip("BaseFigure");
}

Shape::~Shape()
{
    foreach (Shape *p, baseShapeSet)
	{
        p->removeDependentShape(this);
	}

    foreach (Shape *c, dependentShapeSet)
	{
		delete c;
	}

    dependentShapeSet.clear();
    baseShapeSet.clear();
}

void Shape::showBoundingRect(QPainter *painter)
{
    if (getWithBoundingBox())
    {
        QBrush brush(Qt::lightGray);
        QPen pen(brush, 2, Qt::DashLine);
        painter->setPen(pen);
        painter->drawRect(boundingRect());
    }
}

void Shape::addDependentShape(Shape *child)
{
    dependentShapeSet.insert(child);
    child->addBaseShape(this);
}

void Shape::removeDependentShape(Shape *child)
{
	if (child != this)
	{
        dependentShapeSet.remove(child);
	}
}

void Shape::addBaseShape(Shape *parent)
{
    baseShapeSet.insert(parent);
}

QVariant Shape::itemChange(QGraphicsItem::GraphicsItemChange change,
							  const QVariant &value)
{
	if (change == ItemPositionHasChanged && scene())
	{
        foreach (Shape *shape, dependentShapeSet)
		{
            shape->updateItem();
            shape->itemChange(change, value);
		}
	}

	return QGraphicsItem::itemChange(change, value);
}
