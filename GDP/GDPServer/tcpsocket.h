#ifndef TCPSOCKET_H
#define TCPSOCKET_H

#include <QObject>

class GDPMessages;
class QTcpSocket;
class TcpSocket : public QObject
{
	Q_OBJECT

public:
	TcpSocket(QTcpSocket* socket, QObject *parent);
	~TcpSocket();
signals:

public slots :
	void disconnected();
	void bytesWritten(qint64 size);
	void readyRead();
private:
	QTcpSocket*	pSocket;
	GDPMessages* pMessageManager;
};

#endif // TCPSOCKET_H
