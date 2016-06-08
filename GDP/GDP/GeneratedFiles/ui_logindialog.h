/********************************************************************************
** Form generated from reading UI file 'logindialog.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINDIALOG_H
#define UI_LOGINDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LoginDialog
{
public:
    QPushButton *buttonLogin;
    QGroupBox *groupBoxLogin;
    QWidget *formLayoutWidget;
    QFormLayout *formLayoutGPDLogin;
    QLabel *labelUserName;
    QLineEdit *lineEditUserName;
    QLabel *labelPassword;
    QCheckBox *checkBoxStayLoggedIn;
    QLineEdit *lineEditPassword;

    void setupUi(QDialog *LoginDialog)
    {
        if (LoginDialog->objectName().isEmpty())
            LoginDialog->setObjectName(QStringLiteral("LoginDialog"));
        LoginDialog->resize(412, 157);
        buttonLogin = new QPushButton(LoginDialog);
        buttonLogin->setObjectName(QStringLiteral("buttonLogin"));
        buttonLogin->setGeometry(QRect(160, 120, 93, 28));
        groupBoxLogin = new QGroupBox(LoginDialog);
        groupBoxLogin->setObjectName(QStringLiteral("groupBoxLogin"));
        groupBoxLogin->setGeometry(QRect(10, 10, 391, 101));
        groupBoxLogin->setAlignment(Qt::AlignCenter);
        formLayoutWidget = new QWidget(groupBoxLogin);
        formLayoutWidget->setObjectName(QStringLiteral("formLayoutWidget"));
        formLayoutWidget->setGeometry(QRect(0, 20, 391, 103));
        formLayoutGPDLogin = new QFormLayout(formLayoutWidget);
        formLayoutGPDLogin->setObjectName(QStringLiteral("formLayoutGPDLogin"));
        formLayoutGPDLogin->setSizeConstraint(QLayout::SetDefaultConstraint);
        formLayoutGPDLogin->setHorizontalSpacing(7);
        formLayoutGPDLogin->setVerticalSpacing(7);
        formLayoutGPDLogin->setContentsMargins(0, 0, 0, 0);
        labelUserName = new QLabel(formLayoutWidget);
        labelUserName->setObjectName(QStringLiteral("labelUserName"));

        formLayoutGPDLogin->setWidget(0, QFormLayout::LabelRole, labelUserName);

        lineEditUserName = new QLineEdit(formLayoutWidget);
        lineEditUserName->setObjectName(QStringLiteral("lineEditUserName"));

        formLayoutGPDLogin->setWidget(0, QFormLayout::FieldRole, lineEditUserName);

        labelPassword = new QLabel(formLayoutWidget);
        labelPassword->setObjectName(QStringLiteral("labelPassword"));

        formLayoutGPDLogin->setWidget(1, QFormLayout::LabelRole, labelPassword);

        checkBoxStayLoggedIn = new QCheckBox(formLayoutWidget);
        checkBoxStayLoggedIn->setObjectName(QStringLiteral("checkBoxStayLoggedIn"));

        formLayoutGPDLogin->setWidget(2, QFormLayout::LabelRole, checkBoxStayLoggedIn);

        lineEditPassword = new QLineEdit(formLayoutWidget);
        lineEditPassword->setObjectName(QStringLiteral("lineEditPassword"));
        lineEditPassword->setEchoMode(QLineEdit::Password);

        formLayoutGPDLogin->setWidget(1, QFormLayout::FieldRole, lineEditPassword);


        retranslateUi(LoginDialog);

        QMetaObject::connectSlotsByName(LoginDialog);
    } // setupUi

    void retranslateUi(QDialog *LoginDialog)
    {
        LoginDialog->setWindowTitle(QApplication::translate("LoginDialog", "Dialog", 0));
        buttonLogin->setText(QApplication::translate("LoginDialog", "Login", 0));
        groupBoxLogin->setTitle(QApplication::translate("LoginDialog", "Group Picture Developer Login", 0));
        labelUserName->setText(QApplication::translate("LoginDialog", "Username", 0));
        labelPassword->setText(QApplication::translate("LoginDialog", "Password", 0));
        checkBoxStayLoggedIn->setText(QApplication::translate("LoginDialog", "Stay logged in", 0));
    } // retranslateUi

};

namespace Ui {
    class LoginDialog: public Ui_LoginDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINDIALOG_H
