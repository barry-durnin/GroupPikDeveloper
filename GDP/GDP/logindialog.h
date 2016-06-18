/*****************************************************************************
Login widget
Gathers the user login details from the login widget
Communicates with the server and determines if the login details are correct
Closes the widget when login is successful allowing the main window to trigger the groupview widget

Authored by Barry Durnin.
******************************************************************************/
#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QWidget>

namespace Ui
{
	class Login;
}

class LoginDialog : public QWidget
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = 0);
    ~LoginDialog();

private slots:
    void on_buttonLogin_clicked();

private:
	Ui::Login* ui;
};

#endif // LOGINDIALOG_H
