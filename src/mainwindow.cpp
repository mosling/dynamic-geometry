#include <QDebug>
#include <string>
#include <sstream>
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // add a group for the action items
    QActionGroup *actionGroup = new QActionGroup(ui->toolBar);
    ui->actionAddPoint->setActionGroup(actionGroup);
    ui->actionAddSegment->setActionGroup(actionGroup);

    ui->actionKreis->setActionGroup(actionGroup);
    ui->actionSelect->setActionGroup(actionGroup);
    ui->actionLine->setActionGroup(actionGroup);
    ui->actionPointAtCircle->setActionGroup(actionGroup);
    ui->actionDynamicCircle->setActionGroup(actionGroup);
    ui->actionTracker->setActionGroup(actionGroup);
    ui->actionMidPoint->setActionGroup(actionGroup);
    ui->actionCircleIntersection->setActionGroup(actionGroup);

    // create the scene and connect to view
    scene = new GeometryScene();
    const int sceneSize = 800;
    const QRectF sceneRect(0.0, sceneSize, sceneSize, sceneSize);
    scene->setSceneRect(sceneRect);
    scene->setStatusBar(ui->statusBar);

    ui->graphicsView->setScene(scene);
    ui->graphicsView->setRenderHints(QPainter::SmoothPixmapTransform);
    ui->graphicsView->setMinimumSize(sceneSize, sceneSize);
    ui->graphicsView->setMouseTracking(true);

    ui->statusBar->showMessage(QStringLiteral("Dynamic Geometry"));
}

MainWindow::~MainWindow()
{
    delete scene;
    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);
    QRectF bb = scene->sceneRect();
    int w = ui->graphicsView->width();
    int h = ui->graphicsView->height();

    bb.setWidth(bb.width() < w ? w : bb.width());
    bb.setHeight(bb.height() < h ? h : bb.height());

    qDebug() << "set scene size to " << bb.width() << " x " << bb.height();
    scene->setSceneRect(bb);
}

void MainWindow::on_actionSelect_triggered()
{
    qDebug() << "start manipulation";
    scene->setNextNewShape(Shape::OBJECT, nullptr);
}

void MainWindow::on_actionAddPoint_triggered()
{
    qDebug() << "start adding a new point ";
    scene->setNextNewShape(Shape::POINT, QStringLiteral("P"));
}

void MainWindow::on_actionAddSegment_triggered()
{
    qDebug() << "start adding a new segment ";
    scene->setNextNewShape(Shape::SEGMENT, QStringLiteral("PP"));
}

void MainWindow::on_actionKreis_triggered()
{
    qDebug() << "start adding a new circle ";
    scene->setNextNewShape(Shape::CIRCLE, QStringLiteral("PP"));
}

void MainWindow::on_actionLine_triggered()
{
    scene->setNextNewShape(Shape::LINE, QStringLiteral("PP"));
}

void MainWindow::on_actionPointAtCircle_triggered()
{
    scene->setNextNewShape(Shape::DISTPOINT , QStringLiteral("PP"));
}

void MainWindow::on_actionDynamicCircle_triggered()
{
    scene->setNextNewShape(Shape::DYNCIRCLE , QStringLiteral("PC"));
}

void MainWindow::on_actionRemove_triggered()
{
    Q_FOREACH( QGraphicsItem *item, scene->selectedItems() )
    {
        scene->removeItem(item);
        delete item;
    }

    this->update();
}

void MainWindow::on_actionVisible_triggered()
{
    scene->changeVisibility();
}

void MainWindow::on_actionTracker_triggered()
{
    scene->setNextNewShape(Shape::POINTPATH, QStringLiteral("P"));
}

void MainWindow::on_actionCleanTracker_triggered()
{
    Q_FOREACH (QGraphicsItem *item, scene->selectedItems())
    {
        Shape *shape = dynamic_cast<Shape *>(item);
        if (shape->getType() == Shape::POINT)
        {
            Q_FOREACH( Shape *s, shape->getDependentShapeSet())
            {
                if (Shape::POINTPATH == s->getType())
                {
                    qDebug() << "clean tracker " << s->toolTip();
                    scene->removeItem(s);
                    qDebug() << "remove object";
                    delete(s);
                    qDebug() << "add new item";
                    scene->addItem(new PointPath(shape));
                }
            }
        }
    }

    scene->update();
}

void MainWindow::on_actionMidPoint_triggered()
{
    scene->setNextNewShape(Shape::MIDPOINT, QStringLiteral("PP"));
}

void MainWindow::on_actionCircleIntersection_triggered()
{
    scene->setNextNewShape(Shape::CIRCINT, QStringLiteral("CC"));
}
