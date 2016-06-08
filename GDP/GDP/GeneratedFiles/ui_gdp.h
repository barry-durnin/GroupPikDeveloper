/********************************************************************************
** Form generated from reading UI file 'gdp.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GDP_H
#define UI_GDP_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GDPClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *GDPClass)
    {
        if (GDPClass->objectName().isEmpty())
            GDPClass->setObjectName(QStringLiteral("GDPClass"));
        GDPClass->resize(600, 400);
        menuBar = new QMenuBar(GDPClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        GDPClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(GDPClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        GDPClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(GDPClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        GDPClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(GDPClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        GDPClass->setStatusBar(statusBar);

        retranslateUi(GDPClass);

        QMetaObject::connectSlotsByName(GDPClass);
    } // setupUi

    void retranslateUi(QMainWindow *GDPClass)
    {
        GDPClass->setWindowTitle(QApplication::translate("GDPClass", "GDP", 0));
    } // retranslateUi

};

namespace Ui {
    class GDPClass: public Ui_GDPClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GDP_H
