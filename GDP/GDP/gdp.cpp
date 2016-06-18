/*****************************************************************************
Application Main window
Entry point widget.
Spawns the login window and the main widget Group view once the login process os complete

Authored by Barry Durnin.
******************************************************************************/

#include "gdp.h"

#include "groupview.h"
#include "logindialog.h"

/**************************************************************************************************************
Constructor
Create the login widget and show it.
Create an event that watches for the login widget to close
**************************************************************************************************************/
GDP::GDP(QWidget *parent) : QMainWindow(parent), pLogin(NULL), pGroupView(NULL)
{
	ui.setupUi(this);

	
	pLogin = new LoginDialog(this);
	pLogin->setAttribute(Qt::WA_DeleteOnClose);
	connect(pLogin, SIGNAL(destroyed(QObject*)), this, SLOT(LoginClose()));

	setCentralWidget(pLogin);
}

/**************************************************************************************************************
Destructor
Clean up the objects
**************************************************************************************************************/
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
}

/**************************************************************************************************************
Slot function
Triggers when the login widget to closes
Opens the group view widget
**************************************************************************************************************/
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
}