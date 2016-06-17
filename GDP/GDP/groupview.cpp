#include "groupview.h"

//local
#include "camerawidget.h"
#include "groupviewsettings.h"

//qt
#include "ui_groupview.h"
#include "ui_groupviewsettings.h"
#include <QDebug>
#include <QMessageBox>

GroupViewWidget::GroupViewWidget(QWidget *parent) : QWidget(parent), pUI(new Ui::GroupView)
{
	pUI->setupUi(this);
	pScrollAreaWidget = new QWidget();
	pScrollAreaLayout = new QVBoxLayout(pScrollAreaWidget);
	pUI->scrollArea->setWidget(pScrollAreaWidget);
	pUI->scrollArea->setWidgetResizable(true);

	pCamera = new CameraWidget(parent);
	
	//This widget is a fried class, allows access to the ui member within
	pGroupSettingsWidget = new GroupViewSettingsWidget(parent);
	pGroupSettingsWidget->hide();

	connect(pGroupSettingsWidget, SIGNAL(GroupViewSettingsApply()), this, SLOT(GroupSettingsApply()));
	connect(pGroupSettingsWidget, SIGNAL(GroupViewSettingsCancel()), this, SLOT(GroupSettingsCancel()));

	connect(pCamera, SIGNAL(CameraWidgetCloseButton()), this, SLOT(CameraWidgetHide()));
}

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
}

void GroupViewWidget::on_buttonNewGroup_clicked()
{
	//launch a new widget and get the user information
	hide();
	pGroupSettingsWidget->show();
}

void GroupViewWidget::GroupSettingsApply()
{
	//get the information and show updated widgets
	QString name = pGroupSettingsWidget->GetGroupName();
	if (m_groupMap.find(name) == m_groupMap.end())
	{
		QPushButton* pButton = new QPushButton(name);
		GroupNodeData* pNode = new GroupNodeData(pButton);
		m_groupMap[name] = pNode;
		pScrollAreaLayout->addWidget(pButton);

		pGroupSettingsWidget->hide();
		pGroupSettingsWidget->ClearFields();
		connect(pButton, SIGNAL(clicked()), this, SLOT(ActivateCamera()));

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

void GroupViewWidget::GroupSettingsCancel()
{
	pGroupSettingsWidget->ClearFields();
	pGroupSettingsWidget->hide();
	show();
}

void GroupViewWidget::ActivateCamera()
{
	hide();

	Q_ASSERT(pCamera);
	pCamera->show();
}

void GroupViewWidget::CameraWidgetHide()
{
	pCamera->hide();
	show();
}