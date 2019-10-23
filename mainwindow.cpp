#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // create the scene and connect to view
    scene = new GraphicsSelectionScene();
    const int sceneSize = 800;
    const QRectF sceneRect(0.0, sceneSize, sceneSize, sceneSize);
    scene->setSceneRect(sceneRect);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setRenderHints(QPainter::SmoothPixmapTransform);
    ui->graphicsView->setMinimumSize(sceneSize, sceneSize);
}

MainWindow::~MainWindow()
{
    delete scene;
    delete ui;
}


void MainWindow::on_actionPunkt_triggered()
{
    scene->setAddPointMode(ui->actionPunkt->isChecked());
}

void MainWindow::on_actionStrecke_triggered()
{
    scene->setNewFigureType(NsFigure::MIDPOINT);
    scene->setSelectionMode("PP");
}

void MainWindow::on_actionKreis_triggered()
{
    scene->setNewFigureType(NsFigure::CIRCLE);
    scene->setSelectionMode("PP");
}

void MainWindow::on_actionGitter_100x100_triggered()
{
    for (int x=0; x < 100; ++x)
    {
        for (int y=0; y < 100; ++y)
        {
            SKPoint *p = new SKPoint();
            p->setPos(x*10,y*10);
            p->setRadius(4);
            scene->addItem(p);
        }
    }
}
