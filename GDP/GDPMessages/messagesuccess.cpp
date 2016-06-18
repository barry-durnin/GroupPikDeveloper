/*****************************************************************************
Message packet success
Success data message

Authored by Barry Durnin.
******************************************************************************/

#include "messagesuccess.h"

MessageSuccess::MessageSuccess()
{
}

MessageSuccess::~MessageSuccess()
{
}

QByteArray MessageSuccess::CreateMessage(MessageBaseData* data)
{
	return MessageBase::CreateMessageTemplate(success, "");
}

bool MessageSuccess::VerifyMessage(const QByteArray& data)
{
	return false;
}

MessageBaseData* MessageSuccess::ReadMessage(const QByteArray& data)
{
	return new MessageSuccessData();
}