#pragma once

#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QStatusBar>
#include <QList>
#include <QMap>
#include "ShapeList.h"

class GeometryScene : public QGraphicsScene
{
private:
    Q_OBJECT

public:
    GeometryScene(QObject *parent = nullptr);

    void setNextNewShape(Shape::ShapeType aType, const QString &objList);
    void changeVisibility();
    inline void setStatusBar(QStatusBar *value) { statusBar = value; }

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) override;

private:
    void updateStatusMessage();
    bool isCreationMode();
    void createAndAddItem(Shape::ShapeType type);
    void addNewItemAndDisplay(Shape *shape);

    QStatusBar       *statusBar = nullptr;
    QString          selectionString;
    int              selectionStringIndex;
    Shape::ShapeType nextShapeType;
    QList<Shape *>   selectionList;
    QMap<QChar, int> objTypeMap;
    bool             addPointMode;
};
