#include "messagefail.h"

MessageFail::MessageFail()
{
}

MessageFail::~MessageFail()
{
}

QString MessageFail::CreateMessage(MessageBaseData* data)
{
	QString str;
	str.append("HeaderStart");
	str.append(";Type=" + QString::number(data->eType));
	str.append(";HeaderFinish;###");
	return str;
}

bool MessageFail::VerifyMessage(const QString& data)
{
	return true;
}

MessageBaseData* MessageFail::ReadMessage(const QStringList& data)
{
	return new MessageFailData();
}