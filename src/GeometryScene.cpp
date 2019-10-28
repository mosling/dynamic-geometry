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
}

void GeometryScene::setNextNewShape(Shape::ShapeType aType, const QString &objList)
{
    nextShapeType = aType;
    selectionList.clear();
    selectionString = objList;
    selectionStringIndex = 0;

    updateStatusMessage();
}

void GeometryScene::changeVisibility()
{
    foreach (QGraphicsItem *item, this->selectedItems())
    {
        Shape *s = dynamic_cast<Shape *>(item);
        s->setConstructionHelper(!s->isConstructionHelper());
    }
}

void GeometryScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    QGraphicsItem *pItemUnderMouse =
            itemAt(mouseEvent->scenePos().x(),
                   mouseEvent->scenePos().y(),
                   QTransform());

    if (isCreationMode())
    {
        if (Shape::POINT == nextShapeType)
        {
            // points are the only independent elements
            Point *skp = new Point();
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
                for (qint32 i = 0; i < Shape::ShapeType::STOPPER; ++i)
                {
                    if (Shape::typeShortname[i] == selectionString.at(selectionStringIndex)
                            && i == fClass)
                    {
                        qDebug() << "  found matching type " << Shape::typeName[i];
                        selectionList.append(f);
                        pItemUnderMouse->setSelected(true);
                        selectionStringIndex++;
                        break;
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
                    case Shape::DISTPOINT:
                        mp = new PointAtCircle(selectionList.at(0), selectionList.at(1));
                        break;
                    case Shape::DYNCIRCLE:
                        mp = new DynamicCircle(selectionList.at(0), selectionList.at(1));
                        break;
                    case Shape::POINTPATH:
                        mp = new PointPath(selectionList.at(0));
                        break;
                    default:
                        break;
                    }
                    this->addItem(mp);

                    // and setup for the next geometry object
                    setNextNewShape(nextShapeType, selectionString);
                }
                else
                {
                    updateStatusMessage();
                }

                return;
            }
        }
    }

    QGraphicsScene::mousePressEvent(mouseEvent);
}

void GeometryScene::updateStatusMessage()
{
    if (nullptr != statusBar)
    {
        if (isCreationMode())
        {
            QString message = QString("Creating '%1' wait for %2[%3]")
                    .arg(Shape::typeName[nextShapeType])
                    .arg(selectionString)
                    .arg(selectionStringIndex);

            statusBar->showMessage(message);
        }
        else
        {
            statusBar->showMessage("Dynamic Geometry Manipulation Mode");
        }
    }
}

bool GeometryScene::isCreationMode()
{
    return selectionString != nullptr && 0 < selectionString.length();
}
