#include <cmath>
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

void GraphicsSelectionScene::mousePressEvent(QGraphicsSceneMouseEvent *pMouseEvent)
{
    QGraphicsItem* pItemUnderMouse =
            itemAt(pMouseEvent->scenePos().x(),
                   pMouseEvent->scenePos().y(),
                   QTransform());

    qDebug() << "Scene Rectangle: " << this->sceneRect();
    qDebug() << "mouse at scene  : " << pMouseEvent->scenePos();
    qDebug() << "mouse at screen : " << pMouseEvent->screenPos();
    qDebug() << "Wait for " << selectionString;


    if (addPointMode)
    {
        SKPoint *skp = new SKPoint();
        qDebug() << "ready --> adding new point";
        skp->setPos(pMouseEvent->scenePos());
        skp->setZValue(-10);
        this->addItem(skp);
    }
    else if ( pItemUnderMouse &&
              (pItemUnderMouse->flags() & QGraphicsItem::ItemIsSelectable))
    {
        SKFigure *f = dynamic_cast<SKFigure*>(pItemUnderMouse);
        qDebug() << "  object    : " << f->toolTip();
        qDebug() << "  find item : " << f->getTypeClass();
        if ( !selectionString.isEmpty() )
        {
            NsFigure::objEnum fClass = f->getTypeClass();
            qDebug() << "  find item type" << fClass;
            bool match = false;
            QMapIterator<QChar, int> it(objTypeMap);
            while (it.hasNext() && !match)
            {
                it.next();
                if (it.key()==selectionString.at(0) && it.value()==fClass )
                {
                    qDebug() << "found right type " << it.key();
                    match = true;
                    selectionList.append(f);
                    pItemUnderMouse->setSelected(!pItemUnderMouse->isSelected());
                    selectionString.remove(0,1);
                }
            }
            if (selectionString.isEmpty())
            {
                qDebug() << "ready --> construct new object";
                SKFigure *mp = nullptr;
                switch (newType)
                {
                case NsFigure::MIDPOINT:
                    mp = new SKMidPoint(selectionList.at(0), selectionList.at(1) );
                    break;
                case NsFigure::CIRCLE:
                    mp = new SKCircle(selectionList.at(0), selectionList.at(1) );
                    break;
                default:
                    break;
                }
                this->addItem(mp);
            }
            return;
        }
    }
    else
    {
        qDebug() << "  ... no element found";
    }

    QGraphicsScene::mousePressEvent(pMouseEvent);
}

void GraphicsSelectionScene::addItem(QGraphicsItem *item)
{
    QGraphicsScene::addItem(item);
    return;

    if (nullptr != item)
    {
        QRectF sr = this->sceneRect();
        QRectF bb = QRectF(item->pos().x(), item->pos().y(),
                           item->boundingRect().width(), item->boundingRect().height());

        qDebug() << "scene position   : " << item->pos();
        qDebug() << "scene rectangle  : " << sr;
        qDebug() << "item bounding box: " << bb;
        this->setSceneRect(sr.united(bb));
        qDebug() << "resulting scene  : " << this->sceneRect();
    }
}

void GraphicsSelectionScene::removeItem(QGraphicsItem *item)
{
    QGraphicsScene::removeItem(item);
}

void GraphicsSelectionScene::setSelectionMode(const QString &objList)
{
    selectionList.clear();
    selectionString = objList;
    setAddPointMode(false);
    qDebug() << "set selection list " << objList;
}

void GraphicsSelectionScene::setNewFigureType(NsFigure::objEnum aType)
{
    newType = aType;
}

void GraphicsSelectionScene::setAddPointMode(bool aMode)
{
    addPointMode = aMode;
}


