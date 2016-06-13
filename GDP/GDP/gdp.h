#ifndef GDP_H
#define GDP_H

#include <QtWidgets/QMainWindow>
#include "ui_gdp.h"

class GDPMessages;
class LoginDialog;
class CameraWidget;
class GDP : public QMainWindow
{
	Q_OBJECT

public:
	GDP(QWidget *parent = 0);
	~GDP();
    inline GDPMessages* GetMessageManager() const {return pMessageManager;}

public slots:
	void LoginClose();
private:
	Ui::GDPClass ui;
	CameraWidget *pCamera;
    LoginDialog *pLogin;
    GDPMessages* pMessageManager;
};

#endif // GDP_H
