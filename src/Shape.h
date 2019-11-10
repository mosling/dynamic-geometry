#pragma once

#include <QGraphicsItem>
#include <QPainter>
#include <QString>
#include <QList>

#include "ShapeOption.h"

class Shape : public QObject, public QGraphicsItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)

    Q_PROPERTY(bool boundingBox READ boundingBox WRITE setboundingBox NOTIFY boundingBoxChanged )
    Q_PROPERTY(bool helper READ helper WRITE setHelper NOTIFY helperChanged )

public:

    enum ShapeType { TCLASS,    LCLASS,    PCLASS,   CCLASS,  OBJECT,    MULTIFIG,
                     POINT,     SEGMENT,   LINE,     RAY,     CIRCLE,    TEXT,
                     CIRCINT,   INTPOINT,  MIDPOINT, PONLINE, MIRPOINT,  DISTPOINT,
                     MIDLINE,   PLUMBLINE, PARLINE,  HORLINE, ALGORITHM, DYNCIRCLE,
                     POINTPATH, STOPPER
                   };


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
        return m_option;
    }

public Q_SLOTS:
    void setHelper(bool helper)
    {
        m_helper = helper;
    }

    void setboundingBox(bool boundingBox)
    {
        m_boundingBox = boundingBox;
    }

Q_SIGNALS:
    void boundingBoxChanged(bool boundingBox);

    void helperChanged(bool helper);

protected:
    QVariant itemChange(GraphicsItemChange change,
                        const QVariant &value) override;
    QList<Shape *> dependentShapeSet;

private:
    QList<Shape *> baseShapeSet;
    Shape *removingChild;

    bool m_boundingBox;
    bool m_helper;
    ShapeOption m_option;
};
