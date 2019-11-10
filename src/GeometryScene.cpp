#include <cmath>
#include <string>
#include <sstream>
#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsItem>
#include <QGraphicsView>
#include <QMapIterator>

#include "GeometryScene.h"

GeometryScene::GeometryScene(QObject *parent)
    : QGraphicsScene(parent),
      nextShapeType(Shape::STOPPER),
      selectionString(""),
      selectionStringIndex(-1)
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
        s->setHelper(!s->helper());
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
            skp->setZValue(10);
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
                    if (Shape::typeShortname[i] == selectionString.at(selectionStringIndex) && i == fClass)
                    {
                        if (selectionList.contains(f))
                        {
                            qDebug() << "same shape fount ... ignoring";
                        }
                        else
                        {
                            qDebug() << "  found matching type " << Shape::typeName[i];
                            selectionList.append(f);
                            pItemUnderMouse->setSelected(true);
                            selectionStringIndex++;
                            break;
                        }
                    }
                }
                if (selectionStringIndex == selectionString.length())
                {
                    createAndAddItem(nextShapeType);
                    setNextNewShape(nextShapeType, selectionString);
                }
            }
        }
        else if (pItemUnderMouse)
        {
            qDebug() << pItemUnderMouse->toolTip() << " isn't selectable.";
        }
    }

    updateStatusMessage();
    QGraphicsScene::mousePressEvent(mouseEvent);
}

void GeometryScene::createAndAddItem(Shape::ShapeType type)
{
    qDebug() << "Create Shape " << Shape::typeName[type]
                << " with " << selectionList.size() << " elements";

    if (Shape::MIDPOINT == type)
    {
        addNewItemAndDisplay(new MidPoint(selectionList.at(0), selectionList.at(1)));
        Segment *l = new Segment(selectionList.at(0), selectionList.at(1));
        l->setHelper(true);
        l->setZValue(-10);
        addNewItemAndDisplay(l);
    }
    else if (Shape::CIRCLE == type)
    {
        addNewItemAndDisplay(new Circle(selectionList.at(0), selectionList.at(1)));
    }
    else if (Shape::SEGMENT == type)
    {
        addNewItemAndDisplay(new Segment(selectionList.at(0), selectionList.at(1)));
    }
    else if (Shape::LINE == type)
    {
        addNewItemAndDisplay(new Line(selectionList.at(0), selectionList.at(1)));
    }
    else if (Shape::DISTPOINT == type)
    {
        addNewItemAndDisplay(new PointAtCircle(selectionList.at(0), selectionList.at(1)));
        Circle *c = new Circle(selectionList.at(0), selectionList.at(1));
        c->setHelper(true);
        addNewItemAndDisplay(c);
    }
    else if (Shape::DYNCIRCLE == type)
    {
        addNewItemAndDisplay(new DynamicCircle(selectionList.at(0), selectionList.at(1)));
    }
    else if (Shape::POINTPATH == type)
    {
        addNewItemAndDisplay(new PointPath(selectionList.at(0)));
    }
    else if (Shape::CIRCINT == type)
    {
        CircleIntersection *ci = new CircleIntersection(selectionList.at(0), selectionList.at(1));

        Point *p1 = new Point();
        p1->setFlag(QGraphicsItem::ItemIsMovable, false);
        p1->setVisible(false);

        Point *p2 = new Point();
        p2->setFlag(QGraphicsItem::ItemIsMovable, false);
        p2->setVisible(false);

        ci->addDependentShape(p1);
        ci->addDependentShape(p2);

        addNewItemAndDisplay(ci);
        addNewItemAndDisplay(p1);
        addNewItemAndDisplay(p2);
    }
    else
    {
        qDebug() << "no implementation for item " << nextShapeType;
    }
}

void GeometryScene::addNewItemAndDisplay(Shape *shape)
{
    this->addItem(shape);
    shape->updateItem();
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
