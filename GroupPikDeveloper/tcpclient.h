#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <QObject>

class QNetworkSession;
class QObject;
class QTcpSocket;
class TcpClient : public QObject
{
public:
    explicit TcpClient(QObject *parent = 0);
    ~TcpClient();
    void Read();
    bool IsConnected();
private:
    QTcpSocket *pTcpSocket;
    QNetworkSession *pNetworkSession;
};

#endif // TCPCLIENT_H
