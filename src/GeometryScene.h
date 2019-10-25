#pragma once

#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QList>
#include <QMap>
#include "ShapeList.h"

class GeometryScene : public QGraphicsScene
{
public:
    GeometryScene(QObject *parent = nullptr);

    void setNextNewShape(Shape::ShapeType aType, const QString &objList);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);

private:
    QString selectionString;
    int selectionStringIndex;
    Shape::ShapeType nextShapeType;
    QList<Shape *> selectionList;
    QMap<QChar, int> objTypeMap;
    bool addPointMode;
};
