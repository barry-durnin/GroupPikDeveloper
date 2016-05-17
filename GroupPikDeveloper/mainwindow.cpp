#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "cameradialog.h"
#include "camerawidget.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    pCamera = new CameraWidget(this);
}

MainWindow::~MainWindow()
{
    if(pCamera)
    {
        delete pCamera;
    }
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    pCamera->show();
}
