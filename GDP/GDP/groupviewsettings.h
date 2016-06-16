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
	friend class GroupViewWidget;
public:
	explicit GroupViewSettingsWidget(QWidget *parent = 0);
	~GroupViewSettingsWidget();

private slots:
private:
	Ui::GroupViewSettings* pUI;
};

#endif