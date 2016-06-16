#ifndef GDP_H
#define GDP_H

#include <QtWidgets/QMainWindow>
#include "ui_gdp.h"

class CameraWidget;
class GDPMessages;
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
	CameraWidget *pCamera;
	GroupViewWidget* pGroupView;
    LoginDialog *pLogin;
};

#endif // GDP_H
