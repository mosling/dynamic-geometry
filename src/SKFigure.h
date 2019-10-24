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

    virtual inline NsFigure::objEnum getTypeClass() { return NsFigure::OBJECT; }
    virtual inline NsFigure::objEnum getType() { return NsFigure::OBJECT; }
    virtual void updateItem();

    void addBaseFigure(SKFigure *child);
    void removeDependent(SKFigure *child);
    void addDependentFigure(SKFigure *parent);

protected:
    QVariant itemChange(GraphicsItemChange change,
                        const QVariant &value);

private:
    QSet<SKFigure *> *baseFigureSet;
    QSet<SKFigure *> *dependentFigureSet;
    SKFigure         *removingChild;
};

#endif // SKFIGURE_H
