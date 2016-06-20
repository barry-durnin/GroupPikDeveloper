#include "tcpserver.h"
#include "database.h"
#include "tcpsocket.h"

#include <QDebug>
#include <QTcpSocket>
#include <QTcpServer>

namespace gdpserver
{
	sTCPServer::sTCPServer(QObject *parent) : QObject(parent)
	{
		m_server = new QTcpServer(this);

		// whenever a user connects, it will emit signal
		connect(m_server, SIGNAL(newConnection()), this, SLOT(newConnection()));

		if (!m_server->listen(QHostAddress::Any, 9999))
		{
			qDebug() << "Server could not start";
		}
		else
		{
			qDebug() << "Server started";
		}

		m_database = new sDatabase();
	}

	sTCPServer::~sTCPServer()
	{
		for (int i = 0; i < m_connectedSockets.size(); ++i)
		{
			sTCPSocket* pSocket = m_connectedSockets[i];
			if (pSocket)
			{
				delete pSocket;
				pSocket = NULL;
			}
		}
		m_connectedSockets.clear();

		if (m_database)
		{
			delete m_database;
			m_database = nullptr;
		}
		if (m_server)
		{
			delete m_server;
			m_server = nullptr;
		}
	}

	//override qtcpserver newConnection
	void sTCPServer::newConnection()
	{
		qDebug() << "New Connection!";

		//need to grab the socket
		QTcpSocket* pSocket = m_server->nextPendingConnection();
		sTCPSocket* pSocketWrapper = new sTCPSocket(pSocket, this);
		m_connectedSockets.push_back(pSocketWrapper);
	}
}