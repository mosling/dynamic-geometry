#ifndef SHAPEOPTION_H
#define SHAPEOPTION_H

#include <QObject>
#include <QColor>

class ShapeOption : public QObject
{
    Q_OBJECT

public:
    ShapeOption();

    Q_PROPERTY(QColor helperColor READ helperColor WRITE setHelperColor )
    Q_PROPERTY(QColor penColor READ penColor WRITE setPenColor )
    Q_PROPERTY(QColor brushColor READ brushColor WRITE setBrushColor )
    Q_PROPERTY(QColor selectedColor READ selectedColor WRITE setSelectedColor )

    Q_PROPERTY(qreal penWidth READ penWidth WRITE setPenWidth )
    Q_PROPERTY(Qt::PenStyle penStyle READ penStyle WRITE setPenStyle )

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

public slots:

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

private:
    QColor m_helperColor;
    QColor m_penColor;
    QColor m_brushColor;
    QColor m_selectedColor;
    qreal m_penWidth;
    Qt::PenStyle m_penStyle;
};

#endif // SHAPEOPTION_H
