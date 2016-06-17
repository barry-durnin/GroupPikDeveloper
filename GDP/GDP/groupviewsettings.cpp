#include "groupviewsettings.h"

#include "ui_groupviewsettings.h"
#include <QDebug>
#include <QMessageBox>

GroupViewSettingsWidget::GroupViewSettingsWidget(QWidget *parent) : QWidget(parent), pUI(new Ui::GroupViewSettings)
{
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
	emit GroupViewSettingsApply();
}

void GroupViewSettingsWidget::on_pushButtonCancel_clicked()
{
	emit GroupViewSettingsCancel();
}
