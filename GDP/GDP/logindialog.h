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
