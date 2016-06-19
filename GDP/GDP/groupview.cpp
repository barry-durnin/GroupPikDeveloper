/*****************************************************************************
User interaction widget
Dynamically adds groups to the scroll widget and gathers information from the group view widget
Handles group view ui communication from the user input
Spawns the camera widget on group selection

Authored by Barry Durnin.
******************************************************************************/

#include "groupview.h"

//local
#include "camerawidget.h"
#include "groupviewsettings.h"
#include "tcpclient.h"

//message
#include <gdpmessages.h>
#include <messagegroupadd.h>
#include <messagegroupedit.h>

//qt
#include "ui_groupview.h"
#include "ui_groupviewsettings.h"
#include <QDebug>
#include <QMessageBox>

/**************************************************************************************************************
Constructor
Setup the group view widget and initialise events listeners
**************************************************************************************************************/
GroupViewWidget::GroupViewWidget(QWidget *parent) : QWidget(parent), pUI(new Ui::GroupView), pSelectedNode(NULL), pClient(NULL)
{
	//Connect to the server
	pClient = new TcpClient(this);

	pUI->setupUi(this);

	//Set up the scroll area so new widgets can be added to it in a vertical layout
	pScrollAreaWidget = new QWidget();
	pScrollAreaLayout = new QVBoxLayout(pScrollAreaWidget);
	pUI->scrollArea->setWidget(pScrollAreaWidget);
	pUI->scrollArea->setWidgetResizable(true);

	pCamera = new CameraWidget(pClient, parent);

	//This widget is a fried class, allows access to the ui member within
	pGroupSettingsWidget = new GroupViewSettingsWidget(parent);
	pGroupSettingsWidget->hide();

	//Custom signals triggered from the group view settings widget
	connect(pGroupSettingsWidget, SIGNAL(GroupViewSettingsApply()), this, SLOT(GroupSettingsApply()));
	connect(pGroupSettingsWidget, SIGNAL(GroupViewSettingsCancel()), this, SLOT(GroupSettingsCancel()));
	connect(pGroupSettingsWidget, SIGNAL(GroupViewSettingsEdit()), this, SLOT(GroupSettingsEdit()));

	connect(pCamera, SIGNAL(CameraWidgetCloseButton()), this, SLOT(CameraWidgetHide()));
}

/**************************************************************************************************************
Destructor
Clean up the objects
**************************************************************************************************************/
GroupViewWidget::~GroupViewWidget()
{
	for (auto i = m_groupMap.begin(); i != m_groupMap.end(); ++i)
	{
		(*i)->pButton->deleteLater();
		delete (*i);
		(*i) = NULL;
	}
	m_groupMap.clear();

	if (pScrollAreaLayout)
	{
		delete pScrollAreaLayout;
		pScrollAreaLayout = NULL;
	}
	if (pScrollAreaWidget)
	{
		delete pScrollAreaWidget;
		pScrollAreaWidget = NULL;
	}
	if (pGroupSettingsWidget)
	{
		delete pGroupSettingsWidget;
		pGroupSettingsWidget = NULL;
	}
	if (pCamera)
	{
		delete pCamera;
		pCamera = NULL;
	}
	if (pUI)
	{
		delete pUI;
		pUI = NULL;
	}
	if (pClient)
	{
		delete pClient;
		pClient = NULL;
	}
}

/**************************************************************************************************************
Slot function from the New Group Button widget within the ui
**************************************************************************************************************/
void GroupViewWidget::on_buttonNewGroup_clicked()
{
	//launch a new widget and get the user information
	hide();
	pGroupSettingsWidget->EnableEditMode(false);
	pGroupSettingsWidget->show();
}

/**************************************************************************************************************
Slot function from the Remove Group Button widget within the ui
**************************************************************************************************************/
void GroupViewWidget::on_buttonRemoveGroup_clicked()
{
	if (pSelectedNode)
	{
		pScrollAreaLayout->removeWidget(pSelectedNode->pButton);
		m_groupMap.remove(pSelectedNode->m_name);
		pSelectedNode->pButton->deleteLater();
		delete pSelectedNode;
		pSelectedNode = NULL;
	}
	else
	{
		QMessageBox messageBox;
		messageBox.critical(this, "Notice", "No group selected");
		messageBox.setFixedSize(500, 200);
	}
}

/**************************************************************************************************************
Slot function from the Edit Group Button widget within the ui
**************************************************************************************************************/
void GroupViewWidget::on_buttonEditGroup_clicked()
{
	if (pSelectedNode)
	{
		hide();
		pGroupSettingsWidget->PopulateFields(pSelectedNode);
		pGroupSettingsWidget->EnableEditMode(true);
		pGroupSettingsWidget->show();
	}
	else
	{
		QMessageBox messageBox;
		messageBox.critical(this, "Notice", "No group selected");
		messageBox.setFixedSize(500, 200);
	}
}

/**************************************************************************************************************
Custom event slot function
Once the group view settings widget has finished editing the data this event will trigger (Edit button event flow)
**************************************************************************************************************/
void GroupViewWidget::GroupSettingsEdit()
{
	bool bUpdate = false;
	if (pSelectedNode->m_name != pGroupSettingsWidget->GetGroupName())
	{
		bUpdate = true;
	}
	if (pSelectedNode->m_memberList != pGroupSettingsWidget->GetGroupMembers())
	{
		bUpdate = true;
	}

	if (bUpdate)
	{
		GroupNodeData node(NULL, pGroupSettingsWidget->GetGroupName(), pGroupSettingsWidget->GetGroupMembers());
		if (ServerEditGroup(pSelectedNode->m_name, &node))
		{
			m_groupMap.remove(pSelectedNode->m_name);
			pSelectedNode->m_name = pGroupSettingsWidget->GetGroupName();
			pSelectedNode->m_memberList = pGroupSettingsWidget->GetGroupMembers();
			pSelectedNode->pButton->setText(pSelectedNode->m_name);
			m_groupMap[pSelectedNode->m_name] = pSelectedNode;
		}
		else
		{
			qDebug() << "Failed to edit server records on the group";
		}
	}

	pGroupSettingsWidget->hide();
	pGroupSettingsWidget->ClearFields();
	show();
}

/**************************************************************************************************************
On group edit communicate with the server and tell the server about the group the user wishes to edit
old name can be the same as the new name. user may have edited the members etc. this will only be called 
when the group has been edited
**************************************************************************************************************/
bool GroupViewWidget::ServerEditGroup(const QString& oldName, const GroupNodeData* const pNode)
{
	bool bSuccess = false;
	Q_ASSERT(pClient);
	if (pClient->IsConnected())
	{
		MessageBaseData* data = NULL;
		QByteArray message;
		MessageGroupEditData groupData(oldName, pNode->m_name, pNode->m_memberList);
		Q_ASSERT(pClient->GetMessageManager());
		if (!pClient->GetMessageManager()->CreateMessage(message, &groupData))
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
				messageBox.critical(this, "Error", "Failed to create the group on the server");
				messageBox.setFixedSize(500, 200);
				break;
			case success:
				bSuccess = true;
				break;
			default:
				qDebug() << "Unknown message received id: " << data->eType;
				break;
			}
		}
	}
	return bSuccess;
}

/**************************************************************************************************************
On group add communicate with the server and tell the server about the group the user wishes to add
**************************************************************************************************************/
bool GroupViewWidget::ServerAddGroup(const GroupNodeData* const pNode)
{
	bool bSuccess = false;
	Q_ASSERT(pClient);
	if (pClient->IsConnected())
	{
		MessageBaseData* data = NULL;
		QByteArray message;
		MessageGroupAddData groupData(pNode->m_name, pNode->m_memberList);
		Q_ASSERT(pClient->GetMessageManager());
		if (!pClient->GetMessageManager()->CreateMessage(message, &groupData))
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
				messageBox.critical(this, "Error", "Failed to create the group on the server");
				messageBox.setFixedSize(500, 200);
				break;
			case success:
				bSuccess = true;
				break;
			default:
				qDebug() << "Unknown message received id: " << data->eType;
				break;
			}
		}
	}
	return bSuccess;
}

/**************************************************************************************************************
Custom event slot function
Once the group view settings widget has finished editing the data this event will trigger (New group button event flow)
**************************************************************************************************************/
void GroupViewWidget::GroupSettingsApply()
{
	//get the information and show updated widgets
	QString name = pGroupSettingsWidget->GetGroupName();
	QStringList memberList = pGroupSettingsWidget->GetGroupMembers();
	if (m_groupMap.find(name) == m_groupMap.end())
	{
		QPushButton* pButton = new QPushButton(name);
		pButton->setAutoFillBackground(true);

		GroupNodeData* pNode = new GroupNodeData(pButton, name, memberList);
		if (ServerAddGroup(pNode))
		{
			m_groupMap[name] = pNode;
			pScrollAreaLayout->addWidget(pButton);

			pGroupSettingsWidget->hide();
			pGroupSettingsWidget->ClearFields();
			connect(pButton, SIGNAL(clicked()), this, SLOT(GroupButtonClicked()));
		}
		else
		{
			qDebug() << "Critical error. server did not add the group";
			delete pButton;
			delete pNode;
		}

		//Show this updated widget
		show();
	}
	else
	{
		//keep the group view settings widget active and tell the user to change the group name
		QMessageBox messageBox;
		messageBox.critical(this, "Error", "Group already exists, change the group name");
		messageBox.setFixedSize(500, 200);
		return;
	}
}

/**************************************************************************************************************
Loop the group map and reset all the nodes that store groups information
**************************************************************************************************************/
void GroupViewWidget::ResetGroupButtons()
{
	for (auto i = m_groupMap.begin(); i != m_groupMap.end(); ++i)
	{
		(*i)->bSelected = false;
		QPalette p((*i)->pButton->palette());
		p.setBrush(QPalette::Button, Qt::transparent);
		(*i)->pButton->setPalette(p);
	}
	pSelectedNode = NULL;
}

/**************************************************************************************************************
Dynamically created button has been pressed by the user
Check the button information and set it to selected if needed or launch the camera 
if the button is already in a selected state
**************************************************************************************************************/
void GroupViewWidget::GroupButtonClicked()
{
	QPushButton* pButton = static_cast<QPushButton*>(QObject::sender());
	Q_ASSERT(pButton);

	if (m_groupMap.find(pButton->text()) == m_groupMap.end())
	{
		qDebug() << "Critical Error! Group button should be in the group map!";
		return;
	}

	GroupNodeData* pNode = m_groupMap[pButton->text()];
	Q_ASSERT(pNode);

	if (pNode->bSelected)
	{
		ActivateCamera();
	}
	else
	{
		ResetGroupButtons();
		pNode->bSelected = true;

		QPalette p(pButton->palette());
		p.setBrush(QPalette::Button, Qt::color1);
		pButton->setPalette(p);

		pSelectedNode = pNode;
	}
}

/**************************************************************************************************************
Custom event slot function
Once the group view settings widget cancel button has been click thuis event will trigger (Group view settings cancel button pressed)
**************************************************************************************************************/
void GroupViewWidget::GroupSettingsCancel()
{
	pGroupSettingsWidget->ClearFields();
	pGroupSettingsWidget->hide();
	show();
}

/**************************************************************************************************************
Custom event slot function
Once the group view settings widget cancel button has been click this event will trigger (Group view settings cancel button pressed)
**************************************************************************************************************/
void GroupViewWidget::ActivateCamera()
{
	hide();

	Q_ASSERT(pCamera);
	pCamera->show();
}

/**************************************************************************************************************
Hide the camera widget and show this
**************************************************************************************************************/
void GroupViewWidget::CameraWidgetHide()
{
	pCamera->hide();
	show();
}