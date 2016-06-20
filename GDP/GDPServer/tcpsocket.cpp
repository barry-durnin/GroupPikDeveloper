#include "tcpsocket.h"

#include "gdpmessages.h"
#include "messagebase.h"
#include "messagefail.h"
#include "messagefile.h"
#include "messagegroupadd.h"
#include "messagegroupedit.h"
#include "messagelogin.h"
#include "messagesuccess.h"

#include <QImage>
#include <QPixMap>

#include <QTcpSocket>

namespace gdpserver
{
	sTCPSocket::sTCPSocket(QTcpSocket* socket, QObject *parent) : QObject(parent)
	{
		m_socket = socket;
		if (m_socket)
		{
			connect(m_socket, SIGNAL(disconnected()), this, SLOT(disconnected()));
			connect(m_socket, SIGNAL(bytesWritten(qint64)), this, SLOT(bytesWritten(qint64)));
			connect(m_socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
		}
		else
		{
			qDebug() << "No valid socket provided to the TCP socket class";
		}

		m_messageManager = new GDPMessages();
	}

	sTCPSocket::~sTCPSocket()
	{
		if (m_socket)
		{
			m_socket->close();
			delete m_socket;
			m_socket = nullptr;
		}

		if (m_messageManager)
		{
			delete m_messageManager;
			m_messageManager = NULL;
		}
	}

	void sTCPSocket::disconnected()
	{
		qDebug() << "disconnected...";
	}

	void sTCPSocket::bytesWritten(qint64 size)
	{
		qDebug() << "bytesWritten...";
	}

	void sTCPSocket::readyRead()
	{
		qDebug() << "bytesRead...";

		if (m_socket->bytesAvailable())
		{
			bool bSuccess = false;
			MessageLoginData* loginData;
			MessageFileData* fileData;
			MessageGroupAddData* groupAddData;
			MessageGroupEditData* groupEditData;

			QByteArray outMessage = "";
			QByteArray buffer = m_socket->readAll();
			MessageBaseData* data;

			int size = m_messageManager->GetMessageSize(buffer);
			if (buffer.size() < size)
			{
				while (buffer.size() < size)
				{
					m_socket->waitForReadyRead();
					buffer.append(m_socket->readAll());
					//TODO include a break out clause
				}
			}

			data = m_messageManager->ReadMessage(buffer);
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
			case group_add:
				groupAddData = static_cast<MessageGroupAddData*>(data);
				bSuccess = true;
				break;
			case group_edit:
				groupEditData = static_cast<MessageGroupEditData*>(data);
				bSuccess = true;
				break;
			default:
				qDebug() << "Unknown Message id: " << data->eType;
				break;
			}

			if (bSuccess)
			{
				MessageSuccessData successData;
				if (!m_messageManager->CreateMessage(outMessage, &successData))
				{
					qDebug() << "Failed to create success message";
				}
				m_socket->write(outMessage);
			}
			else
			{
				MessageFailData failData;
				if (!m_messageManager->CreateMessage(outMessage, &failData))
				{
					qDebug() << "Failed to create fail message";
				}
				m_socket->write(outMessage);
			}

			if (data)
			{
				delete data;
				data = NULL;
			}
		}

		m_socket->flush();
		m_socket->waitForBytesWritten(1000);
	}
}