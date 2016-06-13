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
    void Write(const QString& message);
    bool IsConnected();
	void WaitForBytesWritten(unsigned int millisecond);
	void WaitForBytesRead();
	void Flush();

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
