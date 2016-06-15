#ifndef MESSAGEBASE_H
#define MESSAGEBASE_H

#include <QByteArray>
#include <QString>

enum MessageType
{
	unknown_message_type,
	fail,
	file,
	login,
	success,
	max_message_type
};

struct MessageBaseData
{
    MessageType eType;
};

class MessageBase
{
private:
    friend class GDPMessages;
protected:
	QByteArray CreateMessageTemplate(MessageType type, const QByteArray& data);
    virtual QByteArray CreateMessage(MessageBaseData* data) = 0;
    virtual bool VerifyMessage(const QByteArray& data) = 0;
	virtual MessageBaseData* ReadMessage(const QByteArray& data) = 0;
public:
    MessageBase();
    virtual ~MessageBase();
};

#endif // MESSAGEBASE_H
