/*****************************************************************************
Message packet fail
Fail message

Authored by Barry Durnin.
******************************************************************************/
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
	bool VerifyMessage(const QByteArray& data);
	MessageBaseData* ReadMessage(const QByteArray& data);
public:
	~MessageFail();
};

#endif //__MESSAGEFAIL_H__