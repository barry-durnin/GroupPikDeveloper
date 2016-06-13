#ifndef MESSAGEBASE_H
#define MESSAGEBASE_H

#include <QString>

enum MessageType
{
	unknown_message_type,
	fail,
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
    virtual QString CreateMessage(MessageBaseData* data) = 0;
    virtual bool VerifyMessage(const QString& data) = 0;
	virtual MessageBaseData* ReadMessage(const QStringList& data) = 0;
public:
    MessageBase();
    virtual ~MessageBase();
};

#endif // MESSAGEBASE_H
