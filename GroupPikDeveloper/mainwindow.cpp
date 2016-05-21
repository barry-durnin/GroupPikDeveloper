#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "camerawidget.h"
#include "logindialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    pCamera = new CameraWidget(this);
    pLogin = new LoginDialog(this);
    pLogin->show();
}

MainWindow::~MainWindow()
{
    if(pLogin)
    {
        delete pLogin;
    }
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
