/*****************************************************************************
Database

Authored by Barry Durnin.
******************************************************************************/

#include "database.h"

#include <QSqlDatabase>
#include <QSqlError>
#include <QDebug>

Database::Database(QObject *parent) : QObject(parent)
{    
    QStringList driverList;
    driverList = QSqlDatabase::drivers();

    if (!driverList.contains("QODBC", Qt::CaseInsensitive))
    {
        qDebug()<<"No QODBC support! Check all needed dll-files!";
    }
    else
    {
        qDebug()<<"QODBC support is avaiable.";
    }

/*    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    db.setHostName("BarryLT");
    //db.setDatabaseName("");
    db.setPort(3306);
    db.setUserName("root");
    db.setPassword("barry");
    bool ok = db.open();
    if(ok)
    {
        qDebug() << "Database Connection successful";
    }
    else
    {
        qDebug() << "Database Connection un-successful ";
        qDebug() << db.lastError();
    }*/

    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("GDP");
    //db.setHostName("127.0.0.1");
    //db.setDatabaseName("");
    //db.setPort(3306);
    //db.setUserName("root");
    //db.setPassword("barry");

    if (!db.open())
    {
        qDebug() << db.lastError().text();
    }
    else
    {
        qDebug("success");
    }
}

Database::~Database()
{

}
