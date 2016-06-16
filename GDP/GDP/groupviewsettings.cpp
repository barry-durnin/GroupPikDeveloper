#include "groupviewsettings.h"

#include "ui_groupviewsettings.h"
#include <QDebug>

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