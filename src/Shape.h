#pragma once

#include <QGraphicsItem>
#include <QPainter>
#include <QString>
#include <QList>

#include "ShapeOption.h"

class Shape : public QGraphicsItem
{
public:

    enum ShapeType { TCLASS,    LCLASS,    PCLASS,   CCLASS,  OBJECT,    MULTIFIG,
                     POINT,     SEGMENT,   LINE,     RAY,     CIRCLE,    TEXT,
                     CIRCINT,   INTPOINT,  MIDPOINT, PONLINE, MIRPOINT,  DISTPOINT,
                     MIDLINE,   PLUMBLINE, PARLINE,  HORLINE, ALGORITHM, DYNCIRCLE,
                     POINTPATH, STOPPER
                   };

    Q_PROPERTY(bool boundingBox READ boundingBox WRITE setboundingBox)
    Q_PROPERTY(bool helper READ helper WRITE setHelper)

    explicit Shape();
    ~Shape() override;

    virtual ShapeType getTypeClass() const { return OBJECT; }
    virtual ShapeType getType() const { return OBJECT; }
    virtual void updateItem() = 0;

    bool allBaseShapesVisible();
    void showBoundingRect(QPainter *painter);
    void setOptions(QPainter *painter);

    void addDependentShape(Shape *child);
    void removeDependentShape(Shape *child);

    const static QList<QString> typeName;
    const static QList<QChar> typeShortname;

    QList<Shape *> getDependentShapeSet() const { return dependentShapeSet; }

    bool helper() const
    {
        return m_helper;
    }

    bool boundingBox() const
    {
        return m_boundingBox;
    }

    ShapeOption &getOption()
    {
        return option;
    }

public slots:
    void setHelper(bool helper)
    {
        m_helper = helper;
        this->setFlag(ItemIsSelectable, !m_helper);
    }

    void setboundingBox(bool boundingBox)
    {
        m_boundingBox = boundingBox;
    }

protected:
    QVariant itemChange(GraphicsItemChange change,
                        const QVariant &value) override;
    QList<Shape *> dependentShapeSet;

private:
    QList<Shape *> baseShapeSet;
    Shape *removingChild;

    bool m_boundingBox;
    bool m_helper;
    ShapeOption option;
};
