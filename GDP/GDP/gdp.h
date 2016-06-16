#ifndef GDP_H
#define GDP_H

#include <QtWidgets/QMainWindow>
#include "ui_gdp.h"

class GroupViewWidget;
class LoginDialog;
class GDP : public QMainWindow
{
	Q_OBJECT

public:
	GDP(QWidget *parent = 0);
	~GDP();

public slots:
	void LoginClose();
private:
	Ui::GDPClass ui;
	GroupViewWidget* pGroupView;
    LoginDialog *pLogin;
};

#endif // GDP_H
