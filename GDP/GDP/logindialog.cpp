/*****************************************************************************
Login widget
Gathers the user login details from the login widget
Communicates with the server and determines if the login details are correct
Closes the widget when login is successful allowing the main window to trigger the groupview widget

Authored by Barry Durnin.
******************************************************************************/
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

/**************************************************************************************************************
Constructor
**************************************************************************************************************/
LoginDialog::LoginDialog(QWidget *parent) : QWidget(parent), ui(new Ui::Login)
{
	ui->setupUi(this);

	//DOnt need to this, override the function with name of the button like this on_buttonLogin_clicked
	// buttonLogin is the name within the widget ui, the clicked is the signal doing the event trigger below will cause this function to be triggered twice
	//connect(ui->buttonLogin, SIGNAL(clicked()), this, SLOT(on_buttonLogin_clicked()));
}

/**************************************************************************************************************
Destructor
Clean up the objects
**************************************************************************************************************/
LoginDialog::~LoginDialog()
{
	if (ui)
	{
		delete ui;
		ui = NULL;
	}
}

/**************************************************************************************************************
Triggered by the login button being pressed
Checks the input data
communicates with the server and verifies the login data
**************************************************************************************************************/
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
