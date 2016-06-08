#include "gdp.h"
#include "camerawidget.h"
#include "logindialog.h"
#include "gdpmessages.h"

GDP::GDP(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
    pMessageManager = new GDPMessages();
    pCamera = new CameraWidget(this);
    pLogin = new LoginDialog(this);
    pLogin->show();
}

GDP::~GDP()
{
    if(pMessageManager)
    {
        delete pMessageManager;
        pMessageManager = NULL;
    }
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
