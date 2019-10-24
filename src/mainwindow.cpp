#include <QDebug>
#include <string>
#include <sstream>
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // add a group for the action items
    QActionGroup *actionGroup = new QActionGroup(ui->toolBar);
    ui->actionPunkt->setActionGroup(actionGroup);
    ui->actionKreis->setActionGroup(actionGroup);
    ui->actionStrecke->setActionGroup(actionGroup);
    ui->actionSelect->setActionGroup(actionGroup);
    ui->actionLine->setActionGroup(actionGroup);

    // create the scene and connect to view
    scene = new GraphicsSelectionScene();
    const int sceneSize = 800;
    const QRectF sceneRect(0.0, sceneSize, sceneSize, sceneSize);
    scene->setSceneRect(sceneRect);

    ui->graphicsView->setScene(scene);
    ui->graphicsView->setRenderHints(QPainter::SmoothPixmapTransform);
    ui->graphicsView->setMinimumSize(sceneSize, sceneSize);
    ui->graphicsView->setMouseTracking(true);

    ui->statusBar->showMessage("Dynamic Geometry");
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

void MainWindow::on_actionPunkt_triggered()
{
    scene->setNewFigureType(NsFigure::POINT, "P");
}

void MainWindow::on_actionStrecke_triggered()
{
    scene->setNewFigureType(NsFigure::MIDPOINT, "PP");
}

void MainWindow::on_actionKreis_triggered()
{
    scene->setNewFigureType(NsFigure::CIRCLE, "PP");
}

void MainWindow::on_actionSelect_triggered()
{
    scene->setNewFigureType(NsFigure::OBJECT, nullptr);
}

void MainWindow::on_actionLine_triggered()
{
    scene->setNewFigureType(NsFigure::LINE, "PP");
}
