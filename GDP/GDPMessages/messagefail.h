#ifndef __MESSAGEFAIL_H__
#define __MESSAGEFAIL_H__

#include "messagebase.h"

struct MessageFailData : public MessageBaseData
{
	MessageFailData()
	{
		eType = fail;
	}
};

class MessageFail : public MessageBase
{
private:
	friend class GDPMessages;
	MessageFail();
	QByteArray CreateMessage(MessageBaseData* data);
	bool VerifyMessage(const QString& data);
	MessageBaseData* ReadMessage(const QStringList& data);
public:
	~MessageFail();
};

#endif //__MESSAGEFAIL_H__