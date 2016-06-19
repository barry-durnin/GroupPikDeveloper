/*****************************************************************************
User interaction widget
Dynamically adds groups to the scroll widget and gathers information from the group view widget
Handles group view ui communication from the user input
Spawns the camera widget on group selection

Authored by Barry Durnin.
******************************************************************************/

#ifndef __GROUPVIEW_H__
#define __GROUPVIEW_H__

#include <QMap>
#include <QWidget>

class CameraWidget;
class GroupViewSettingsWidget;
class TcpClient;

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
	bool ServerAddGroup(const GroupNodeData* const pNode);
	bool ServerEditGroup(const QString& oldName, const GroupNodeData* const pNode);
	//internal widget manipulation
	Ui::GroupView* pUI;
	QWidget*	pScrollAreaWidget;
	QVBoxLayout* pScrollAreaLayout;

	//Controlled widgets
	CameraWidget *pCamera;
	GroupViewSettingsWidget* pGroupSettingsWidget;

	//Internal logic of groups
	QMap<QString, GroupNodeData*> m_groupMap;
	GroupNodeData* pSelectedNode;

	//Networking
	TcpClient* pClient;
};

#endif