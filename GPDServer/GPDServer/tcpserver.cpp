#include "tcpserver.h"

#include <QDebug>
#include <QTcpSocket>
#include <QTcpServer>

TcpServer::TcpServer(QObject *parent) : QObject(parent)
{
    pServer = new QTcpServer(this);
    // whenever a user connects, it will emit signal
    connect(pServer, SIGNAL(newConnection()), this, SLOT(newConnection()));

    if(!pServer->listen(QHostAddress::Any, 9999))
    {
        qDebug() << "Server could not start";
    }
    else
    {
        qDebug() << "Server started";
    }
}

TcpServer::~TcpServer()
{
    if(pServer)
    {
        delete pServer;
    }
}

//override qtcpserver newConnection
void TcpServer::newConnection()
{
    qDebug() << "New Connection!";

    //need to grab the socket
    QTcpSocket *pSocket = pServer->nextPendingConnection();

    pSocket->write("Hello client\r\n");
    pSocket->flush();

    int milliseconds = 1000;
    pSocket->waitForBytesWritten(milliseconds);

    pSocket->close();
    delete pSocket;
}
