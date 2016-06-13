#include "tcpsocket.h"

#include "gdpmessages.h"
#include "messagebase.h"
#include "messagefail.h"
#include "messagelogin.h"
#include "messagesuccess.h"

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
	qDebug() << "disconnected...";
}

void TcpSocket::bytesWritten(qint64 size)
{
	qDebug() << "bytesWritten...";
}

void TcpSocket::readyRead()
{
	qDebug() << "bytesRead...";

	if (pSocket->bytesAvailable())
	{
		MessageLoginData* loginData;

		QString outMessage = "";
		QByteArray buffer = pSocket->readAll();
		QString stream(buffer);
		MessageBaseData* data = pMessageManager->ReadMessage(stream);
		switch (data->eType)
		{
		case login:
			//look in the database, for now check user name for our names just for testing
			loginData = static_cast<MessageLoginData*>(data);
			if (loginData->szUser.contains("barry") || loginData->szUser.contains("robert"))
			{
				MessageSuccessData successData;
				pMessageManager->CreateMessage(outMessage, &successData);
				pSocket->write(outMessage.toStdString().c_str());
			}
			else
			{
				MessageFailData failData;
				pMessageManager->CreateMessage(outMessage, &failData);
				pSocket->write(outMessage.toStdString().c_str());
			}
			break;
		default:
			qDebug() << "Unknown Message";
			break;
		}

		if (data)
		{
			delete data;
			data = NULL;
		}
	}
	pSocket->flush();
	pSocket->waitForBytesWritten(1000);
}