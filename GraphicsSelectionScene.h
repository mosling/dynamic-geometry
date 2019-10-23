#ifndef GRAPHICSSELECTIONSCENE_H
#define GRAPHICSSELECTIONSCENE_H

#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QList>
#include <QMap>
#include "AllFigures.h"

class GraphicsSelectionScene : public QGraphicsScene
{
public:
    GraphicsSelectionScene(QObject *parent = 0);

    void setNewFigureType(NsFigure::objEnum aType);
    void setSelectionMode(const QString &objList);
    void setAddPointMode(bool aMode);

    virtual void addItem(QGraphicsItem *item);
    virtual void removeItem(QGraphicsItem *item);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* pMouseEvent);

private:
    QString selectionString;
    NsFigure::objEnum newType;
    QList<SKFigure *> selectionList;
    QMap<QChar, int> objTypeMap;
    bool addPointMode;
};

#endif // GRAPHICSSELECTIONSCENE_H
