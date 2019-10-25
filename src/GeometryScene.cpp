#include <cmath>
#include <string>
#include <sstream>
#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsItem>
#include <QMapIterator>
#include "GeometryScene.h"

GeometryScene::GeometryScene(QObject *parent)
    : QGraphicsScene(parent), selectionString("")
{
    objTypeMap['P'] = Shape::PCLASS;
}

void GeometryScene::setNextNewShape(Shape::ShapeType aType, const QString &objList)
{
    nextShapeType = aType;
    selectionList.clear();
    selectionString = objList;
    selectionStringIndex = 0;

    qDebug() << "set selection list for "
             << Shape::typeName[aType]
             << " to "
             << selectionString;
}

void GeometryScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    QGraphicsItem *pItemUnderMouse =
        itemAt(mouseEvent->scenePos().x(),
               mouseEvent->scenePos().y(),
               QTransform());

    if (selectionString != nullptr && 0 < selectionString.length())
    {
        qDebug() << "Wait for " << selectionString << "[" << selectionStringIndex << "]";

        if (Shape::POINT == nextShapeType)
        {
            // points are the only independent elements
            Point *skp = new Point();
            qDebug() << "  --> adding new point";
            skp->setPos(mouseEvent->scenePos());
            skp->setZValue(-10);
            this->addItem(skp);
        }
        else if (pItemUnderMouse &&
                 (pItemUnderMouse->flags() & QGraphicsItem::ItemIsSelectable))
        {
            // all other figures depends on points and other figures
            Shape *f = dynamic_cast<Shape *>(pItemUnderMouse);
            qDebug() << "  object    : " << f->toolTip();
            if (selectionStringIndex < selectionString.length())
            {
                Shape::ShapeType fClass = f->getTypeClass();
                qDebug() << "  item class" << Shape::typeName[fClass];
                bool match = false;
                QMapIterator<QChar, int> it(objTypeMap);
                while (it.hasNext() && !match)
                {
                    it.next();
                    if (it.key() == selectionString.at(selectionStringIndex) && it.value() == fClass)
                    {
                        qDebug() << "  found matching type " << it.key();
                        match = true;
                        selectionList.append(f);
                        pItemUnderMouse->setSelected(!pItemUnderMouse->isSelected());
                        selectionStringIndex++;
                    }
                }
                if (selectionStringIndex == selectionString.length())
                {
                    qDebug() << "  --> construct new object";
                    Shape *mp = nullptr;
                    switch (nextShapeType)
                    {
                    case Shape::MIDPOINT:
                        mp = new MidPoint(selectionList.at(0), selectionList.at(1));
                        break;
                    case Shape::CIRCLE:
                        mp = new Circle(selectionList.at(0), selectionList.at(1));
                        break;
                    case Shape::LINE:
                        mp = new Line(selectionList.at(0), selectionList.at(1));
                        break;
                    default:
                        break;
                    }
                    this->addItem(mp);
                    // and setup for the next geometry object
                    setNextNewShape(nextShapeType, selectionString);
                }
                return;
            }
        }
    }

    QGraphicsScene::mousePressEvent(mouseEvent);
}
