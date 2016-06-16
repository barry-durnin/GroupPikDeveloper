#include "groupview.h"

//local
#include "camerawidget.h"
#include "groupviewsettings.h"

//qt
#include "ui_groupview.h"
#include "ui_groupviewsettings.h"
#include <QDebug>

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
	//connect the settings widget button pressed to signal this widget. this widget will know when cancel and apply buttons have been clicked
	connect(pGroupSettingsWidget->pUI->pushButtonApply, SIGNAL(clicked()), this, SLOT(GroupSettingsApplyButton()));
	connect(pGroupSettingsWidget->pUI->pushButtonCancel, SIGNAL(clicked()), this, SLOT(GroupSettingsCancelButton()));
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

void GroupViewWidget::GroupSettingsApplyButton()
{
	pGroupSettingsWidget->hide();
	//get the information and show updated widgets

	QPushButton* pButton = new QPushButton("test");
	GroupNodeData* pNode = new GroupNodeData(pButton);
	m_groupMap["Camera Test Launch"] = pNode;
	pScrollAreaLayout->addWidget(pButton);
	connect(pButton, SIGNAL(clicked()), this, SLOT(ActivateCamera()));
	
	//Show this updated widget
	show();
}

void GroupViewWidget::GroupSettingsCancelButton()
{
	pGroupSettingsWidget->hide();
	show();
}

void GroupViewWidget::ActivateCamera()
{
	hide();

	Q_ASSERT(pCamera);
	pCamera->show();
}
