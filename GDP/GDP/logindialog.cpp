#include "logindialog.h"

//Local
#include "gdp.h"
#include "tcpclient.h"

//Message library
#include <gdpmessages.h>
#include <messagebase.h>
#include <messagelogin.h>

//QT
#include "ui_logindialog.h"
#include <QDebug>
#include <QMessageBox>

LoginDialog::LoginDialog(QWidget *parent) : QWidget(parent), ui(new Ui::Login)
{
	ui->setupUi(this);
	//connect(ui->buttonLogin, SIGNAL(clicked()), this, SLOT(on_buttonLogin_clicked()));
}

LoginDialog::~LoginDialog()
{
	if (ui)
	{
		delete ui;
		ui = NULL;
	}
}

void LoginDialog::on_buttonLogin_clicked()
{
	MessageBaseData* data = NULL;
	
	bool bSuccess = false;
	QByteArray message = "";
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
	TcpClient* pClient = new TcpClient(this);
	if (pClient->IsConnected())
	{
		if (ui->checkBoxStayLoggedIn->checkState() == Qt::Checked)
		{
			//stay logged in is checked. store some information that this device is verified and login automatically next launch
		}

		MessageLoginData loginData(username, password);
		Q_ASSERT(pClient->GetMessageManager());
		if (!pClient->GetMessageManager()->CreateMessage(message, &loginData))
		{
			//error
		}

		pClient->Write(message);
		pClient->Flush();
		pClient->WaitForBytesWritten(1000);

		pClient->WaitForBytesRead();
		data = pClient->GetLastMessage();
		if (data)
		{
			QMessageBox messageBox;
			switch (data->eType)
			{
			case fail:
				messageBox.critical(this, "Error", "Failed to login, use username is barry or robert. password can be anything not setup but must not be an empty field");
				messageBox.setFixedSize(500, 200);
				break;
			case success:
				bSuccess = true;
				break;
			default:
				qDebug() << "Unknown message recieved id: " << data->eType;
				break;
			}
		}
	}

	//close connection
	delete pClient;
	pClient = NULL;

	if (bSuccess)
	{
		close();
	}
}
