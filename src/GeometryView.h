#pragma once

#include <QGraphicsView>

class GeometryView : public QGraphicsView
{
    Q_OBJECT

public:
    GeometryView(QWidget *parent = nullptr);

    void wheelEvent ( QWheelEvent * event ) override;

private slots:
    void scalingTime(qreal x);
    void animFinished();

private:
    int _numScheduledScalings;
};

