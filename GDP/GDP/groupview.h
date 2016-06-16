#ifndef __GROUPVIEW_H__
#define __GROUPVIEW_H__

#include <QMap>
#include <QWidget>

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
	}
	GroupNodeData(QPushButton* button)
	{
		pButton = button;
	}
	QPushButton* pButton;
};

class GroupViewWidget : public QWidget
{
	Q_OBJECT

public:
	explicit GroupViewWidget(QWidget *parent = 0);
	~GroupViewWidget();

private slots:
	void on_buttonNewGroup_clicked();

private:
	Ui::GroupView* pUI;

	QWidget*	pScrollAreaWidget;
	QVBoxLayout* pScrollAreaLayout;

	QMap<QString, GroupNodeData*> m_groupMap;
};

#endif