#include "tcpclient.h"

#include "gdpmessages.h"
#include "messagebase.h"

#include <QNetworkSession>
#include <QObject>
#include <QTcpSocket>

TcpClient::TcpClient(QObject* parent) : QObject(parent), pMessageManager(NULL)
{
    pTcpSocket = new QTcpSocket(this);
	connect(pTcpSocket, SIGNAL(disconnected()), this, SLOT(disconnected()));
	connect(pTcpSocket, SIGNAL(bytesWritten(qint64)), this, SLOT(bytesWritten(qint64)));
	connect(pTcpSocket, SIGNAL(readyRead()), this, SLOT(readyRead()));

    qDebug() << "Client socket connecting to host";
    pTcpSocket->connectToHost("127.0.0.1", 9999);
    pTcpSocket->waitForConnected();

	pMessageManager = new GDPMessages();

	m_lastMessage = NULL;
}

TcpClient::~TcpClient()
{
	if (pMessageManager)
	{
		delete pMessageManager;
		pMessageManager = NULL;
	}
    if(pTcpSocket)
    {
        pTcpSocket->close();
        delete pTcpSocket;
		pTcpSocket = NULL;
    }
}

bool TcpClient::IsConnected()
{
    return pTcpSocket->state() == QAbstractSocket::ConnectedState;
}



void TcpClient::disconnected()
{
	qDebug() << "disconnected...";
}

void TcpClient::bytesWritten(qint64 size)
{
	qDebug() << "bytesWritten...";
}

void TcpClient::readyRead()
{
	qDebug() << "bytesRead...";
	Q_ASSERT(pMessageManager);

	if (m_lastMessage)
	{
		delete m_lastMessage;
		m_lastMessage = NULL;
	}

	if (pTcpSocket->bytesAvailable())
	{
		QByteArray bytes = pTcpSocket->readAll();
		m_lastMessage = pMessageManager->ReadMessage(bytes);
	}
}

void TcpClient::Write(const QString& message)
{
    pTcpSocket->write(message.toStdString().c_str());
}

void TcpClient::WaitForBytesWritten(unsigned int millisecond)
{
	pTcpSocket->waitForBytesWritten(millisecond);
}

void TcpClient::WaitForBytesRead()
{
	pTcpSocket->waitForReadyRead(5000);
}

void TcpClient::Flush()
{
	pTcpSocket->flush();
}