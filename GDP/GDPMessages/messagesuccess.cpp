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

bool MessageSuccess::VerifyMessage(const QByteArrayList& data)
{
	return false;
}

MessageBaseData* MessageSuccess::ReadMessage(const QByteArrayList& data)
{
	return new MessageSuccessData();
}