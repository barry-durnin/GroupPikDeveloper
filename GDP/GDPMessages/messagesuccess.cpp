#include "messagesuccess.h"

MessageSuccess::MessageSuccess()
{
}

MessageSuccess::~MessageSuccess()
{
}

QString MessageSuccess::CreateMessage(MessageBaseData* data)
{
	QString str;
	str.append("HeaderStart");
	str.append(";Type=" + QString::number(data->eType));
	str.append(";HeaderFinish;###");
	return str;
}

bool MessageSuccess::VerifyMessage(const QString& data)
{
	return false;
}

MessageBaseData* MessageSuccess::ReadMessage(const QStringList& data)
{
	return new MessageSuccessData();
}