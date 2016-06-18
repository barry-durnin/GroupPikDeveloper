/*****************************************************************************
Tcp socket
Listens for and writes data

Authored by Barry Durnin.
******************************************************************************/

#include "tcpsocket.h"

#include "gdpmessages.h"
#include "messagebase.h"
#include "messagefail.h"
#include "messagefile.h"
#include "messagelogin.h"
#include "messagesuccess.h"

#include <QImage>
#include <QPixMap>

#include <QTcpSocket>

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
		bool bSuccess = false;
		MessageLoginData* loginData;
		MessageFileData* fileData;

		QByteArray outMessage = "";
		QByteArray buffer = pSocket->readAll();
		MessageBaseData* data;

		unsigned int size = pMessageManager->GetMessageSize(buffer);
		if (buffer.size() < size)
		{
			while (buffer.size() < size)
			{
				pSocket->waitForReadyRead();
				buffer.append(pSocket->readAll());
				//TODO include a break out clause
			}
		}


		data = pMessageManager->ReadMessage(buffer);
		switch (data->eType)
		{
		case login:
			//look in the database, for now check user name for our names just for testing
			loginData = static_cast<MessageLoginData*>(data);
			if (loginData->szUser.contains("barry") || loginData->szUser.contains("robert"))
			{
				bSuccess = true;
			}
			break;
		case file:
			fileData = static_cast<MessageFileData*>(data);
			if (fileData->szFile.size() > 0)
			{
				//640*480
				QImage img(640, 480, QImage::Format_Indexed8);
				img = QImage::fromData(fileData->szFile, "PNG");

				if (img.save("image.png"))
				{
					bSuccess = true;
				}
			}
			break;
		default:
			qDebug() << "Unknown Message id: " << data->eType;
			break;
		}

		if (bSuccess)
		{
			MessageSuccessData successData;
			if (!pMessageManager->CreateMessage(outMessage, &successData))
			{
				qDebug() << "Failed to create sucess message";
			}
			pSocket->write(outMessage);
		}
		else
		{
			MessageFailData failData;
			if (!pMessageManager->CreateMessage(outMessage, &failData))
			{
				qDebug() << "Failed to create fail message";
			}
			pSocket->write(outMessage);
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