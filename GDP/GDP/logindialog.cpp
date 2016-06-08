#include "logindialog.h"

//Local
#include "tcpclient.h"
#include "messagelogin.h"
#include "gdp.h"

//Message library
#include <gdpmessages.h>
#include <messagebase.h>

//QT
#include "ui_logindialog.h"
#include <QMessageBox>

LoginDialog::LoginDialog(QWidget *parent) : QDialog(parent, Qt::CustomizeWindowHint | Qt::WindowTitleHint | Qt::WindowMinMaxButtonsHint), ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
	//connect(ui->buttonLogin, SIGNAL(clicked()), this, SLOT(on_buttonLogin_clicked()));
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::on_buttonLogin_clicked()
{
    QString message = "";
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
    if(client->IsConnected())
    {
        if(ui->checkBoxStayLoggedIn->checkState() == Qt::Checked)
        {
        //stay logged in is checked. store some information that this device is verified and login automatically next launch
        }


        //Get main window
		GDP* mainWindow = (GDP*)parent();
        if(mainWindow)
        {
            MessageLoginData loginData(username, password);
			MessageLoginData loginData1;
            Q_ASSERT(mainWindow->GetMessageManager());
            if(!mainWindow->GetMessageManager()->CreateMessage(message, &loginData))
            {
                //error
            }
			//mainWindow->GetMessageManager()->ReadMessage(message);
        }

        client->Write(message);
    }
}
