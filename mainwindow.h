#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGridLayout>
#include "GraphicsSelectionScene.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
	void on_actionPunkt_triggered();

	void on_actionStrecke_triggered();

        void on_actionGitter_100x100_triggered();

        void on_actionKreis_triggered();

private:
    Ui::MainWindow *ui;
	 QGridLayout *layout;
	 GraphicsSelectionScene *scene;
};

#endif // MAINWINDOW_H
