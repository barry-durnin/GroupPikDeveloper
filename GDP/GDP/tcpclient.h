/*****************************************************************************
Tcp client object
Socket communication with the server
Handles read and writes via the common message library

Authored by Barry Durnin.
******************************************************************************/
#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <QObject>

class GDPMessages;
struct MessageBaseData;

class QNetworkSession;
class QObject;
class QTcpSocket;
class TcpClient : public QObject
{
	Q_OBJECT

public:
    explicit TcpClient(QObject *parent = 0);
    ~TcpClient();
    void Write(const QByteArray& message);
    bool IsConnected();
	void WaitForBytesWritten(unsigned int millisecond);
	void WaitForBytesRead();
	void Flush();
	

	inline GDPMessages* GetMessageManager() const { return pMessageManager; }
	inline MessageBaseData* GetLastMessage() { return m_lastMessage; }
signals:

public slots:
	void disconnected();
	void bytesWritten(qint64 size);
	void readyRead();
private:
    QTcpSocket *pTcpSocket;
	GDPMessages* pMessageManager;
	MessageBaseData* m_lastMessage;
};

#endif // TCPCLIENT_H
