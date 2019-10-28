#pragma once

#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QStatusBar>
#include <QList>
#include <QMap>
#include "ShapeList.h"

class GeometryScene : public QGraphicsScene
{
public:
    GeometryScene(QObject *parent = nullptr);

    void setNextNewShape(Shape::ShapeType aType, const QString &objList);
    void removeSelectedShapes();
    void changeVisibility();
    inline void setStatusBar(QStatusBar *value) { statusBar = value; }

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) override;

private:
    void updateStatusMessage();
    bool isCreationMode();

    QStatusBar       *statusBar = nullptr;
    QString          selectionString;
    int              selectionStringIndex;
    Shape::ShapeType nextShapeType;
    QList<Shape *>   selectionList;
    QMap<QChar, int> objTypeMap;
    bool             addPointMode;
};
