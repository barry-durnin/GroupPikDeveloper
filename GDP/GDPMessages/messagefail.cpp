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

bool MessageFail::VerifyMessage(const QByteArrayList& data)
{
	return true;
}

MessageBaseData* MessageFail::ReadMessage(const QByteArrayList& data)
{
	return new MessageFailData();
}