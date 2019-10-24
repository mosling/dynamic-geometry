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
    GraphicsSelectionScene(QObject *parent = nullptr);

    void setNewFigureType(NsFigure::objEnum aType, const QString &objList);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);

private:
    QString           selectionString;
    int               selectionStringIndex;
    NsFigure::objEnum newType;
    QList<SKFigure *> selectionList;
    QMap<QChar, int>  objTypeMap;
    bool              addPointMode;
};

#endif // GRAPHICSSELECTIONSCENE_H
