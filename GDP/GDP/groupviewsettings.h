#ifndef __GROUPVIEWSETTINGS_H__
#define __GROUPVIEWSETTINGS_H__

#include <QWidget>

namespace Ui
{
	class GroupViewSettings;
}

class GroupViewSettingsWidget : public QWidget
{
	Q_OBJECT
public:
	explicit GroupViewSettingsWidget(QWidget *parent = 0);
	~GroupViewSettingsWidget();

	void ClearFields();
	QString GetGroupName();
signals:
	void GroupViewSettingsApply();
	void GroupViewSettingsCancel();
private slots :
	void on_pushButtonApply_clicked();
	void on_pushButtonCancel_clicked();

private:
	Ui::GroupViewSettings* pUI;
};

#endif