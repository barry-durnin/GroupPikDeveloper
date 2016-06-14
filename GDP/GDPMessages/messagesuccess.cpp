#include "messagesuccess.h"

MessageSuccess::MessageSuccess()
{
}

MessageSuccess::~MessageSuccess()
{
}

QByteArray MessageSuccess::CreateMessage(MessageBaseData* data)
{
	QByteArray bytes;
	bytes.append("HeaderStart");
	bytes.append(";Type=" + QString::number(data->eType));
	bytes.append(";HeaderFinish;###");
	return bytes;
}

bool MessageSuccess::VerifyMessage(const QString& data)
{
	return false;
}

MessageBaseData* MessageSuccess::ReadMessage(const QStringList& data)
{
	return new MessageSuccessData();
}