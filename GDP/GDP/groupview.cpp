#include "groupview.h"

#include "ui_groupview.h"
#include <QDebug>

GroupViewWidget::GroupViewWidget(QWidget *parent) : QWidget(parent), pUI(new Ui::GroupView)
{
	pUI->setupUi(this);
	pScrollAreaWidget = new QWidget();
	pScrollAreaLayout = new QVBoxLayout(pScrollAreaWidget);
	pUI->scrollArea->setWidget(pScrollAreaWidget);
	pUI->scrollArea->setWidgetResizable(true);
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
	if (pUI)
	{
		delete pUI;
		pUI = NULL;
	}
}

void GroupViewWidget::on_buttonNewGroup_clicked()
{
	//launch a new widget and get the user information

	QPushButton* pButton = new QPushButton("test");
	GroupNodeData* pNode = new GroupNodeData(pButton);
	m_groupMap["test"] = pNode;
	
	pScrollAreaLayout->addWidget(pButton);
}


