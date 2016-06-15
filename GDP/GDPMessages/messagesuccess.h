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
	QByteArray CreateMessage(MessageBaseData* data);
	bool VerifyMessage(const QByteArray& data);
	MessageBaseData* ReadMessage(const QByteArray& data);
public:
	~MessageSuccess();
};

#endif //__MESSAGESUCCESS_H__