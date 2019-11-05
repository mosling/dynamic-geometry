#pragma once

#include <QGraphicsView>

class GeometryView : public QGraphicsView
{
private:
    Q_OBJECT

public:
    GeometryView(QWidget *parent = nullptr);

    void wheelEvent ( QWheelEvent * event ) override;


private Q_SLOTS:
    void scalingTime(qreal x);
    void animFinished();

private:
    int _numScheduledScalings;
};

