#include "tcpsocket.h"

#include "gdpmessages.h"
#include "messagebase.h"

#include <QTcpSocket>
//#include <QByteArray>

TcpSocket::TcpSocket(QTcpSocket* socket, QObject *parent) : QObject(parent)
{
	pSocket = socket;
	if (pSocket)
	{
		connect(pSocket, SIGNAL(disconnected()), this, SLOT(disconnected()));
		connect(pSocket, SIGNAL(bytesWritten(qint64)), this, SLOT(bytesWritten(qint64)));
		connect(pSocket, SIGNAL(readyRead()), this, SLOT(readyRead()));

		pSocket->write("Hello client\r\n");
		pSocket->flush();

		int milliseconds = 1000;
		pSocket->waitForBytesWritten(milliseconds);
	}
	else
	{
		qDebug() << "No valid socket provided to the tcp socket class";
	}

	pMessageManager = new GDPMessages();
}

TcpSocket::~TcpSocket()
{
	if (pSocket)
	{
		pSocket->close();
		delete pSocket;
		pSocket = NULL;
	}
	if (pMessageManager)
	{
		delete pMessageManager;
		pMessageManager = NULL;
	}
}

void TcpSocket::disconnected()
{
	if (pSocket)
	{
		pSocket->close();
		delete pSocket;
		pSocket = NULL;
	}
}

void TcpSocket::bytesWritten(qint64 size)
{
	qDebug() << "bytesWritten...";
}

void TcpSocket::readyRead()
{
	if (pSocket->bytesAvailable())
	{
		QByteArray buffer = pSocket->readAll();
		QString stream(buffer);
		MessageBaseData data = pMessageManager->ReadMessage(stream);
		switch (data.eType)
		{
		case login:
			qDebug() << "Login message";
			break;
		default:
			qDebug() << "Unknown Message";
			break;
		}
	}
}