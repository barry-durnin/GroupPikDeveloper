/*****************************************************************************
Group settings widget
Communication with the group view settings widget
Gathers the user information about the group that is to be created or edited
Fires events to groupview class to gather the information

Authored by Barry Durnin.
******************************************************************************/
#include "groupviewsettings.h"

//local
#include "groupview.h"

//QT
#include "ui_groupviewsettings.h"
#include <QDebug>
#include <QMessageBox>

/**************************************************************************************************************
Constructor
**************************************************************************************************************/
GroupViewSettingsWidget::GroupViewSettingsWidget(QWidget *parent) : QWidget(parent), pUI(new Ui::GroupViewSettings)
{
	bEditMode = false;
	pUI->setupUi(this);

	int alignW = (parent->width() - width()) * 0.5f;
	int alignH = (parent->height() - height()) * 0.5f;

	move(alignW, alignH);
}

/**************************************************************************************************************
Destructor
Clean up the objects
**************************************************************************************************************/
GroupViewSettingsWidget::~GroupViewSettingsWidget()
{
	if (pUI)
	{
		delete pUI;
		pUI = NULL;
	}
}

/**************************************************************************************************************
Clear all text from all ui data fields
**************************************************************************************************************/
void GroupViewSettingsWidget::ClearFields()
{
	pUI->lineEditGroupName->setText("");
	pUI->lineEditMembers->setText("");
}

/**************************************************************************************************************
return the text within the group name field
**************************************************************************************************************/
QString GroupViewSettingsWidget::GetGroupName()
{
	return pUI->lineEditGroupName->text();
}

/**************************************************************************************************************
return the text within the group member field as a list separated by spaces
**************************************************************************************************************/
QStringList GroupViewSettingsWidget::GetGroupMembers()
{
	return pUI->lineEditMembers->text().split(" ");
}

/**************************************************************************************************************
Function slot triggered by the ui apply button
Triggers the custom apply or edit signals back to the groupview widget
**************************************************************************************************************/
void GroupViewSettingsWidget::on_pushButtonApply_clicked()
{
	if (pUI->lineEditGroupName->text().length() <= 0)
	{
		QMessageBox messageBox;
		messageBox.critical(this, "Error", "Group needs a name");
		messageBox.setFixedSize(500, 200);
		return;
	}
	if (pUI->lineEditMembers->text().length() <= 0)
	{
		QMessageBox messageBox;
		messageBox.critical(this, "Error", "No members added to the group");
		messageBox.setFixedSize(500, 200);
		return;
	}
	if (bEditMode)
	{
		emit GroupViewSettingsEdit();
	}
	else
	{
		emit GroupViewSettingsApply();
	}
}

/**************************************************************************************************************
Function slot triggered by the ui cancel button
Triggers the custom cancel signals back to the groupview widget
**************************************************************************************************************/
void GroupViewSettingsWidget::on_pushButtonCancel_clicked()
{
	emit GroupViewSettingsCancel();
}

/**************************************************************************************************************
populate the data fields within the widget with the selected group information passed to the function
**************************************************************************************************************/
void GroupViewSettingsWidget::PopulateFields(const GroupNodeData* const pSelectedNode)
{
	Q_ASSERT(pSelectedNode);
	pUI->lineEditGroupName->setText(pSelectedNode->pButton->text());
	pUI->lineEditMembers->setText(pSelectedNode->m_memberList.join(" "));
}