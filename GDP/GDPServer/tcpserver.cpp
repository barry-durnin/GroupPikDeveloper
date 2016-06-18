/*****************************************************************************
Tcp server
Main class, handles the socket connection, incomming connection and message reading and writing

Authored by Barry Durnin.
******************************************************************************/

#include "tcpserver.h"
#include"database.h"
#include "tcpsocket.h"

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

    pDatabase = NULL;//new Database(parent);
}

TcpServer::~TcpServer()
{
	for (int i = 0; i < m_connectedSockets.size(); ++i)
	{
		TcpSocket* pSocket = m_connectedSockets[i];
		if (pSocket)
		{
			delete pSocket;
			pSocket = NULL;
		}
	}
	m_connectedSockets.clear();

    if(pDatabase)
    {
        delete pDatabase;
		pDatabase = NULL;
    }
    if(pServer)
    {
        delete pServer;
		pServer = NULL;
    }
}

//override qtcpserver newConnection
void TcpServer::newConnection()
{
    qDebug() << "New Connection!";

    //need to grab the socket
    QTcpSocket* pSocket = pServer->nextPendingConnection();
	TcpSocket* pSocketWrapper = new TcpSocket(pSocket, this);
	m_connectedSockets.push_back(pSocketWrapper);
}
