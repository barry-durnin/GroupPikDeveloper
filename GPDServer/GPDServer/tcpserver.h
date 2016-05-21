#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QObject>

class QTcpServer;
class TcpServer : public QObject
{
    Q_OBJECT
public:
    explicit TcpServer(QObject *parent = 0);
    ~TcpServer();
signals:

public slots:
    void newConnection();
private:
    QTcpServer *pServer;
};

#endif // TCPSERVER_H
