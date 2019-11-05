#pragma once

#include <QObject>
#include <QColor>

class ShapeOption : QObject
{
private:
    Q_OBJECT

public:
    ShapeOption();
    virtual ~ShapeOption();


    Q_PROPERTY(QColor helperColor READ helperColor WRITE setHelperColor NOTIFY helperChanged )
    Q_PROPERTY(QColor penColor READ penColor WRITE setPenColor NOTIFY penColorChanged )
    Q_PROPERTY(QColor brushColor READ brushColor WRITE setBrushColor NOTIFY brushColorChanged )
    Q_PROPERTY(QColor selectedColor READ selectedColor WRITE setSelectedColor NOTIFY selectedColorChanged )

    Q_PROPERTY(qreal penWidth READ penWidth WRITE setPenWidth NOTIFY penWidthChanged )
    Q_PROPERTY(Qt::PenStyle penStyle READ penStyle WRITE setPenStyle NOTIFY penStyleChanged )

    QColor helperColor() const
    {
        return m_helperColor;
    }

    QColor penColor() const
    {
        return m_penColor;
    }

    QColor brushColor() const
    {
        return m_brushColor;
    }

    QColor selectedColor() const
    {
        return m_selectedColor;
    }

    qreal penWidth() const
    {
        return m_penWidth;
    }

    Qt::PenStyle penStyle() const
    {
        return m_penStyle;
    }

public Q_SLOTS:
    void setHelperColor(QColor helperColor)
    {
        m_helperColor = helperColor;
    }

    void setPenColor(QColor penColor)
    {
        m_penColor = penColor;
    }

    void setBrushColor(QColor brushColor)
    {
        m_brushColor = brushColor;
    }

    void setSelectedColor(QColor selectedColor)
    {
        m_selectedColor = selectedColor;
    }

    void setPenWidth(qreal penWidth)
    {
        m_penWidth = penWidth;
    }

    void setPenStyle(Qt::PenStyle penStyle)
    {
        m_penStyle = penStyle;
    }

Q_SIGNALS:
    void helperChanged(QColor helperColor);

    void penColorChanged(QColor penColor);

    void brushColorChanged(QColor brushColor);

    void selectedColorChanged(QColor selectedColor);

    void penWidthChanged(qreal penWidth);

    void penStyleChanged(Qt::PenStyle penStyle);

private:
    QColor m_helperColor;
    QColor m_penColor;
    QColor m_brushColor;
    QColor m_selectedColor;
    qreal m_penWidth;
    Qt::PenStyle m_penStyle;
};
