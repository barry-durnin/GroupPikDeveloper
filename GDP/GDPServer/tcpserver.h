#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QObject>
#include <QVector>

class Database;
class TcpSocket;

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
    Database *pDatabase;
	QVector<TcpSocket*> m_connectedSockets;
};

#endif // TCPSERVER_H

