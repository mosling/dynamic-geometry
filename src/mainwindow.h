#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGridLayout>
#include "GeometryScene.h"

namespace Ui
{
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    virtual void resizeEvent(QResizeEvent *event);

private slots:
    void on_actionPunkt_triggered();

    void on_actionStrecke_triggered();

    void on_actionKreis_triggered();

    void on_actionSelect_triggered();

    void on_actionLine_triggered();

    void on_actionPointAtCircle_triggered();

    void on_actionDynamicCircle_triggered();

    void on_actionRemove_triggered();

    void on_actionVisible_triggered();

    void on_actionTracker_triggered();

    void on_actionCleanTracker_triggered();

    void on_actionMidPoint_triggered();

    void on_actionCircleIntersection_triggered();

private:
    Ui::MainWindow *ui;
    QGridLayout *layout;
    GeometryScene *scene;
};

#endif // MAINWINDOW_H
