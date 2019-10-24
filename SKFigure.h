#ifndef SKFIGURE_H
#define SKFIGURE_H

#include <QGraphicsItem>
#include <QPainter>
#include <QString>
#include "FigureTypes.h"

class SKFigure : public QGraphicsItem
{
public:
    explicit SKFigure();
    ~SKFigure();

    enum { PointType = UserType + 1, SegmentType, MidPoint, Circle };

    virtual inline NsFigure::objEnum getTypeClass() { return NsFigure::OBJECT; }
    virtual inline NsFigure::objEnum getType() { return NsFigure::OBJECT; }
    virtual void updateItem();

    void addChild(SKFigure *child);
    void removeChild(SKFigure *child);
    void addParent(SKFigure *parent);

protected:
    QVariant itemChange(GraphicsItemChange change,
                        const QVariant &value);

private:
    QSet<SKFigure *> *childs;
    QSet<SKFigure *> *parents;
    SKFigure         *removingChild;
};

#endif // SKFIGURE_H
