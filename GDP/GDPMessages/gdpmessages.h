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

	bool CreateMessage(QString& output, MessageBaseData* data);
	bool VerifyMessage(const QString& stream);
	MessageBaseData ReadMessage(const QString& stream);
private:
	QMap<int, MessageBase*> m_mapMessages;
};

#endif // GDPMESSAGES_H
