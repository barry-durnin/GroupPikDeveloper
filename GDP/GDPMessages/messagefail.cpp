/*****************************************************************************
Message packet fail
Fail message

Authored by Barry Durnin.
******************************************************************************/
#include "messagefail.h"

MessageFail::MessageFail()
{
}

MessageFail::~MessageFail()
{
}

QByteArray MessageFail::CreateMessage(MessageBaseData* data)
{
	return MessageBase::CreateMessageTemplate(fail, "");
}

bool MessageFail::VerifyMessage(const QByteArray& data)
{
	return true;
}

MessageBaseData* MessageFail::ReadMessage(const QByteArray& data)
{
	return new MessageFailData();
}