#pragma once

#include <QGraphicsItem>
#include <QPainter>
#include <QString>

class Shape : public QGraphicsItem
{
public:
    enum ShapeType { TCLASS,  LCLASS,    PCLASS,   CCLASS,  OBJECT,    MULTIFIG,
                     POINT,   SEGMENT,   LINE,     RAY,     CIRCLE,    TEXT,
                     CIRCINT, INTPOINT,  MIDPOINT, PONLINE, MIRPOINT,  DISTPOINT,
                     MIDLINE, PLUMBLINE, PARLINE,  HORLINE, ALGORITHM, DYNCIRCLE,
                     STOPPER
                   };

    explicit Shape();
    ~Shape() override;

    virtual ShapeType getTypeClass() const { return OBJECT; }
    virtual ShapeType getType() const { return OBJECT; }

    virtual void updateItem() = 0;

    void addDependentShape(Shape *child);
    void removeDependentShape(Shape *child);
    void addBaseShape(Shape *parent);

    const static QString typeName[];
    const static QChar typeShortname[];

    bool getWithBoundingBox() const { return withBoundingBox; }
    void setWithBoundingBox(bool value) { withBoundingBox = value; }

protected:
    QVariant itemChange(GraphicsItemChange change,
                        const QVariant &value) override;

private:
    QSet<Shape *> *dependentShapeSet;
    QSet<Shape *> *baseShapeSet;
    Shape *removingChild;
    bool withBoundingBox;
};
