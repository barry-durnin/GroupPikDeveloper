#ifndef __MESSAGESUCCESS_H__
#define __MESSAGESUCCESS_H__

#include "messagebase.h"

struct MessageSuccessData : public MessageBaseData
{
	MessageSuccessData()
	{
		eType = success;
	}
};

class MessageSuccess : public MessageBase
{
private:
	friend class GDPMessages;
	MessageSuccess();
	QString CreateMessage(MessageBaseData* data);
	bool VerifyMessage(const QString& data);
	MessageBaseData* ReadMessage(const QStringList& data);
public:
	~MessageSuccess();
};

#endif //__MESSAGESUCCESS_H__