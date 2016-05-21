#include "logindialog.h"
#include "ui_logindialog.h"

#include "tcpclient.h"

#include <QMessageBox>

LoginDialog::LoginDialog(QWidget *parent) : QDialog(parent, Qt::CustomizeWindowHint | Qt::WindowTitleHint | Qt::WindowMinMaxButtonsHint), ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::on_buttonLogin_clicked()
{
    QString username = ui->lineEditUserName->text();
    QString password = ui->lineEditPassword->text();
    if(username.length() <= 0)
    {
        QMessageBox messageBox;
        messageBox.critical(this,"Error","A username is required");
        messageBox.setFixedSize(500,200);
        return;
    }
    if(password.length() <= 0)
    {
        QMessageBox messageBox;
        messageBox.critical(this,"Error","A password is required");
        messageBox.setFixedSize(500,200);
        return;
    }

    //connect to the login server
    TcpClient* client = new TcpClient(this);
    client->IsConnected();

    if(ui->checkBoxStayLoggedIn->checkState() == Qt::Checked)
    {
        //stay logged in is checked. store some information that this device is verified and login automatically next launch
    }
}
