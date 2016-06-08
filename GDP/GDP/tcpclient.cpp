#include "tcpclient.h"
#include <QNetworkSession>
#include <QObject>
#include <QTcpSocket>

TcpClient::TcpClient(QObject* parent) : QObject(parent)
{
    pTcpSocket = new QTcpSocket(this);
    connect(pTcpSocket, &QIODevice::readyRead, this, &TcpClient::Read);

    qDebug() << "Client socket connecting to host";
    pTcpSocket->connectToHost("127.0.0.1", 9999);
    pTcpSocket->waitForConnected();
}

TcpClient::~TcpClient()
{
    if(pTcpSocket)
    {
        pTcpSocket->close();
        delete pTcpSocket;
    }
}

bool TcpClient::IsConnected()
{
    return pTcpSocket->state() == QAbstractSocket::ConnectedState;
}

void TcpClient::Read()
{
    if (pTcpSocket->bytesAvailable())
    {
        QByteArray bytes = pTcpSocket->readAll();
        qDebug() << bytes;
    }
}

void TcpClient::Write(const QString& message)
{
    pTcpSocket->write(message.toStdString().c_str());
}
