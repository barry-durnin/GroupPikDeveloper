/*****************************************************************************
Message library manager

Generates message data packets 
Reads message data packets

Authored by Barry Durnin.
******************************************************************************/

#ifndef GDPMESSAGES_H
#define GDPMESSAGES_H

#include <QString>
#include <QMap>

struct MessageBaseData;
class MessageBase;
class GDPMessages
{
public:
	GDPMessages();
	~GDPMessages();

	bool CreateMessage(QByteArray& output, MessageBaseData* data);
	bool VerifyMessage(const QByteArray& stream);
	MessageBaseData* ReadMessage(const QByteArray& stream);
	unsigned int GetMessageSize(const QByteArray& stream);
private:
	QMap<int, MessageBase*> m_mapMessages;
};

#endif // GDPMESSAGES_H
