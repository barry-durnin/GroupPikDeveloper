/*****************************************************************************
Tcp client object
Socket communication with the server
Handles read and writes via the common message library

Authored by Barry Durnin.
******************************************************************************/

#include "tcpclient.h"

#include "gdpmessages.h"
#include "messagebase.h"

#include <QNetworkSession>
#include <QObject>
#include <QTcpSocket>

/**************************************************************************************************************
Constructor
Setup a socket connection to the server
Initialise new events to listen for socket key events
**************************************************************************************************************/
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

/**************************************************************************************************************
Destructor
Clean up the objects
**************************************************************************************************************/
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

/**************************************************************************************************************
Check the state of the socket
**************************************************************************************************************/
bool TcpClient::IsConnected()
{
    return pTcpSocket->state() == QAbstractSocket::ConnectedState;
}

/**************************************************************************************************************
Event signal triggered on socket disconnect
**************************************************************************************************************/
void TcpClient::disconnected()
{
	qDebug() << "disconnected...";
}

/**************************************************************************************************************
Event signal triggered on socket writing data
**************************************************************************************************************/
void TcpClient::bytesWritten(qint64 size)
{
	qDebug() << "bytesWritten...";
}

/**************************************************************************************************************
Event signal triggered on socket data read
**************************************************************************************************************/
void TcpClient::readyRead()
{
	qDebug() << "bytesRead...";
	Q_ASSERT(pMessageManager);

	if (m_lastMessage)
	{
		delete m_lastMessage;
		m_lastMessage = NULL;
	}

	//TODO update this to match the way the server reads data. get the header data and 
	// read the size of the packet then wait for that much data to come through
	if (pTcpSocket->bytesAvailable())
	{
		QByteArray bytes = pTcpSocket->readAll();
		m_lastMessage = pMessageManager->ReadMessage(bytes);
	}
}

/**************************************************************************************************************
Write data to the server
**************************************************************************************************************/
void TcpClient::Write(const QByteArray& message)
{
    pTcpSocket->write(message);
}

/**************************************************************************************************************
Wait for the data to be written to the server
**************************************************************************************************************/
void TcpClient::WaitForBytesWritten(unsigned int millisecond)
{
	pTcpSocket->waitForBytesWritten(millisecond);
}

/**************************************************************************************************************
Wait for bytes of data to be read
**************************************************************************************************************/
void TcpClient::WaitForBytesRead()
{
	pTcpSocket->waitForReadyRead(5000);
}

/**************************************************************************************************************
Flush the socket to triiger the write process
**************************************************************************************************************/
void TcpClient::Flush()
{
	pTcpSocket->flush();
}
