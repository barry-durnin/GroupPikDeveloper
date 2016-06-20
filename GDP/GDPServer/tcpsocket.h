#pragma once

#include <QObject>

class GDPMessages;
class QTcpSocket;

namespace gdpserver
{
	class sTCPSocket : public QObject
	{
		Q_OBJECT

	public:
		sTCPSocket(QTcpSocket* socket, QObject *parent);
		~sTCPSocket();

	public slots :
		void disconnected();
		void bytesWritten(qint64 size);
		void readyRead();

	private:
		QTcpSocket*		m_socket;
		GDPMessages*	m_messageManager;
	};
}
