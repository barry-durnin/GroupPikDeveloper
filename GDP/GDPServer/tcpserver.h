#pragma once

#include <QObject>
#include <QVector>

class QTcpServer;

namespace gdpserver
{
	class sDatabase;
	class sTCPSocket;

	class sTCPServer : public QObject
	{
		Q_OBJECT
	public:
		explicit sTCPServer(QObject *parent = 0);
		~sTCPServer();
	signals:

	public slots :
		void newConnection();

	private:
		QTcpServer*				m_server;
		QVector<sTCPSocket*>	m_connectedSockets;
		sDatabase*				m_database;	// @todo: Move this somewhere more sane.
	};
}