#include "gdp.h"
#include "camerawidget.h"
#include "logindialog.h"
#include "gdpmessages.h"

GDP::GDP(QWidget *parent) : QMainWindow(parent), pCamera(NULL), pLogin(NULL)
{
	ui.setupUi(this);

	
	pLogin = new LoginDialog(this);
	pLogin->setAttribute(Qt::WA_DeleteOnClose);
	connect(pLogin, SIGNAL(destroyed(QObject*)), this, SLOT(LoginClose()));

	setCentralWidget(pLogin);
}

GDP::~GDP()
{
    if(pLogin)
    {
        delete pLogin;
        pLogin = NULL;
    }
	if (pCamera)
	{
		delete pCamera;
		pCamera = NULL;
	}
}

void GDP::LoginClose()
{
	//login windows has been detroyed and the pointer released by qt. null the pointer for safty
	pLogin = NULL;

	pCamera = new CameraWidget(this);
	setCentralWidget(pCamera);
	if (pCamera)
	{
		pCamera->show();
	}
}