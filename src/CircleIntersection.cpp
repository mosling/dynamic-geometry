#include <QDebug>
#include "CircleIntersection.h"
#include "GeometryFunction.h"

CircleIntersection::CircleIntersection(Shape *obj1, Shape *obj2)
{
    getOption().setPenColor(QColor(79, 106, 25));
    getOption().setBrushColor(QColor(122, 163, 39));
    getOption().setPenWidth(3.0);

    c1 = dynamic_cast<Circle *>(obj1);
    c2 = dynamic_cast<Circle *>(obj2);

    c1->addDependentShape(this);
    c2->addDependentShape(this);

    setToolTip("Circle Intersection");
}

void CircleIntersection::updateItem()
{
    QList<QPointF> l = GeometryFunction::circleIntersection(*c1, *c2);

    for (int i = 0; i < dependentShapeSet.size(); ++i)
    {
        if (l.size() > i)
        {
            dependentShapeSet.at(i)->setPos(l.at(i));
            dependentShapeSet.at(i)->setVisible(true);
        }
        else
        {
            dependentShapeSet.at(i)->setVisible(false);
        }
    }

    prepareGeometryChange();
}

QRectF CircleIntersection::boundingRect() const
{
    if (dependentShapeSet.size() == 2)
    {
        return GeometryFunction::getBoundingBox(dependentShapeSet.at(0)->scenePos(),
                                                dependentShapeSet.at(1)->scenePos());
    }

    return QRectF(0,0,0,0);
}

void CircleIntersection::paint(QPainter *painter,
                   const QStyleOptionGraphicsItem *option,
                   QWidget *widget)
{
    (void)painter;
    (void)option;
    (void)widget;
}