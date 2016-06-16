#include "gdp.h"

#include "camerawidget.h"
#include "gdpmessages.h"
#include "groupview.h"
#include "logindialog.h"

GDP::GDP(QWidget *parent) : QMainWindow(parent), pCamera(NULL), pLogin(NULL), pGroupView(NULL)
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
	if (pGroupView)
	{
		delete pGroupView;
		pGroupView = NULL;
	}
	if (pCamera)
	{
		delete pCamera;
		pCamera = NULL;
	}
}

void GDP::LoginClose()
{
	//login windows has been destroyed and the pointer released by qt. null the pointer for safety
	pLogin = NULL;

	pGroupView = new GroupViewWidget(this);
	setCentralWidget(pGroupView);
	if (pGroupView)
	{
		pGroupView->show();
	}

//	pCamera = new CameraWidget(this);
//	setCentralWidget(pCamera);
// 	if (pCamera)
// 	{
// 		pCamera->show();
// 	}
}