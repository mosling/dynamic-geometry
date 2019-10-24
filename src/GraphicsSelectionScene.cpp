#include <cmath>
#include <string>
#include <sstream>
#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsItem>
#include <QMapIterator>
#include "GraphicsSelectionScene.h"

GraphicsSelectionScene::GraphicsSelectionScene(QObject *parent)
    : QGraphicsScene(parent), selectionString("")
{
    objTypeMap['P'] = NsFigure::PCLASS;
}

void GraphicsSelectionScene::setNewFigureType(NsFigure::objEnum aType, const QString &objList)
{
    newType = aType;
    selectionList.clear();
    selectionString = objList;
    selectionStringIndex = 0;

    qDebug() << "set selection list for "
             << NsFigure::objName[aType]
             << " to "
             << selectionString;
}

void GraphicsSelectionScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    QGraphicsItem* pItemUnderMouse =
            itemAt(mouseEvent->scenePos().x(),
                   mouseEvent->scenePos().y(),
                   QTransform());

    if (selectionString != nullptr && 0 < selectionString.length())
    {
        qDebug() << "Wait for " << selectionString << "[" << selectionStringIndex << "]";

        if (NsFigure::POINT == newType)
        {
            // points are the only independent elements
            SKPoint *skp = new SKPoint();
            qDebug() << "  --> adding new point";
            skp->setPos(mouseEvent->scenePos());
            skp->setZValue(-10);
            this->addItem(skp);
        }
        else if ( pItemUnderMouse &&
                  (pItemUnderMouse->flags() & QGraphicsItem::ItemIsSelectable))
        {
            // all other figures depends on points and other figures
            SKFigure *f = dynamic_cast<SKFigure*>(pItemUnderMouse);
            qDebug() << "  object    : " << f->toolTip();
            if ( selectionStringIndex < selectionString.length() )
            {
                NsFigure::objEnum fClass = f->getTypeClass();
                qDebug() << "  item class" << NsFigure::objName[fClass];
                bool match = false;
                QMapIterator<QChar, int> it(objTypeMap);
                while (it.hasNext() && !match)
                {
                    it.next();
                    if (it.key()==selectionString.at(selectionStringIndex)
                            && it.value()==fClass )
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
                    SKFigure *mp = nullptr;
                    switch (newType)
                    {
                    case NsFigure::MIDPOINT:
                        mp = new SKMidPoint(selectionList.at(0), selectionList.at(1) );
                        break;
                    case NsFigure::CIRCLE:
                        mp = new SKCircle(selectionList.at(0), selectionList.at(1) );
                        break;
                    case NsFigure::LINE:
                        mp = new SKLine(selectionList.at(0), selectionList.at(1) );
                        break;
                    default:
                        break;
                    }
                    this->addItem(mp);
                    // and setup for the next geometry object
                    setNewFigureType(newType, selectionString);
                }
                return;
            }
        }
    }

    QGraphicsScene::mousePressEvent(mouseEvent);
}
