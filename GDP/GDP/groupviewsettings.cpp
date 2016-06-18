#include "groupviewsettings.h"

//local
#include "groupview.h"

//QT
#include "ui_groupviewsettings.h"
#include <QDebug>
#include <QMessageBox>

GroupViewSettingsWidget::GroupViewSettingsWidget(QWidget *parent) : QWidget(parent), pUI(new Ui::GroupViewSettings)
{
	bEditMode = false;
	pUI->setupUi(this);
}

GroupViewSettingsWidget::~GroupViewSettingsWidget()
{
	if (pUI)
	{
		delete pUI;
		pUI = NULL;
	}
}

void GroupViewSettingsWidget::ClearFields()
{
	pUI->lineEditGroupName->setText("");
	pUI->lineEditMembers->setText("");
}

QString GroupViewSettingsWidget::GetGroupName()
{
	return pUI->lineEditGroupName->text();
}

QStringList GroupViewSettingsWidget::GetGroupMembers()
{
	return pUI->lineEditMembers->text().split(" ");
}

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

void GroupViewSettingsWidget::on_pushButtonCancel_clicked()
{
	emit GroupViewSettingsCancel();
}

void GroupViewSettingsWidget::PopulateFields(const GroupNodeData* const pSelectedNode)
{
	Q_ASSERT(pSelectedNode);
	pUI->lineEditGroupName->setText(pSelectedNode->pButton->text());
	pUI->lineEditMembers->setText(pSelectedNode->m_memberList.join(" "));
}