#include "messagebase.h"

MessageBase::MessageBase()
{

}

MessageBase::~MessageBase()
{

}

QByteArray MessageBase::CreateMessageTemplate(MessageType type, const QByteArray& data)
{
	QByteArray str;
	str.append("HeaderStart");
	str.append(";Size=********");
	str.append(";Type=" + QString::number(type));
	str.append(";HeaderFinish;#");
	str.append(data);
	str.append("\0");

	QString size = QString::number(str.size());
	Q_ASSERT(size.size() < 8);
	str.replace(17, size.size(), size.toUtf8());

	return str;
}