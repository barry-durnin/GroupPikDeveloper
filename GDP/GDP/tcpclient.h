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
    void Write(const QString& message);
    bool IsConnected();
private:
    QTcpSocket *pTcpSocket;
};

#endif // TCPCLIENT_H
