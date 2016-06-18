/*****************************************************************************
Application Main window
Entry point widget.
Spawns the login window and the main widget Group view once the login process os complete

Authored by Barry Durnin.
******************************************************************************/

#include "gdp.h"
#include "groupview.h"

#include "logindialog.h"
#include <QGridLayout>
#include <QPushButton>

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

	int alignW = (width() - pLogin->width()) * 0.5f;
	int alignH = (height() - pLogin->height()) * 0.5f;

	pLogin->move(alignW, alignH);

	/*Cant get the spacing to work as I want wtf*/
#if 0
	QWidget *widget = new QWidget(this);

	pLogin = new LoginDialog(widget);
	pLogin->setAttribute(Qt::WA_DeleteOnClose);
	connect(pLogin, SIGNAL(destroyed(QObject*)), this, SLOT(LoginClose()));


	QSpacerItem* spacer = new QSpacerItem(1, 1);


	QPushButton *button1 = new QPushButton("One");

	QGridLayout *layout = new QGridLayout;
	layout->addWidget(spacer, 0, 0);
	layout->addWidget(pLogin, 0, 1, -1, -1);
	layout->addItem(spacer, 0, 2);


	//Qt::AlignVCenter
	//layout->addWidget(button4, 2, 0);
	//layout->addWidget(button5, 2, 1);

	widget->setLayout(layout);
	setCentralWidget(widget);
#endif
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