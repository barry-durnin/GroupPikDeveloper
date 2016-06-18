#ifndef __GROUPVIEWSETTINGS_H__
#define __GROUPVIEWSETTINGS_H__

#include <QWidget>

struct GroupNodeData;

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
	QStringList GetGroupMembers();
	void PopulateFields(const GroupNodeData* const pSelectedNode);
	void EnableEditMode(bool bModeEdit) { bEditMode = bModeEdit; };
signals:
	void GroupViewSettingsApply();
	void GroupViewSettingsEdit();
	void GroupViewSettingsCancel();
private slots :
	void on_pushButtonApply_clicked();
	void on_pushButtonCancel_clicked();

private:
	bool bEditMode;
	Ui::GroupViewSettings* pUI;
};

#endif