#ifndef __GROUPVIEW_H__
#define __GROUPVIEW_H__

#include <QMap>
#include <QWidget>

class CameraWidget;
class GroupViewSettingsWidget;

class QPushButton;
class QVBoxLayout;
class QWidget;

namespace Ui
{
	class GroupView;
}

struct GroupNodeData 
{
	GroupNodeData()
	{
		pButton = NULL;
		bSelected = false;
		m_name = "";
	}
	GroupNodeData(QPushButton* button, QString name, QStringList memberList) : GroupNodeData()
	{
		pButton = button;
		m_memberList = memberList;
		m_name = name;
	}
	QPushButton* pButton;
	bool bSelected;
	QStringList m_memberList;
	QString m_name;
};

class GroupViewWidget : public QWidget
{
	Q_OBJECT

public:
	explicit GroupViewWidget(QWidget *parent = 0);
	~GroupViewWidget();

	void ResetGroupButtons();
	void ActivateCamera();
private slots:
	void on_buttonNewGroup_clicked();
	void on_buttonRemoveGroup_clicked();
	void on_buttonEditGroup_clicked();
	void GroupSettingsApply();
	void GroupSettingsEdit();
	void GroupSettingsCancel();
	void GroupButtonClicked();
	void CameraWidgetHide();
private:
	Ui::GroupView* pUI;
	QWidget*	pScrollAreaWidget;
	QVBoxLayout* pScrollAreaLayout;

	CameraWidget *pCamera;

	GroupViewSettingsWidget* pGroupSettingsWidget;

	QMap<QString, GroupNodeData*> m_groupMap;
	GroupNodeData* pSelectedNode;
};

#endif