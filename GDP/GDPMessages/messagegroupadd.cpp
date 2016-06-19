/*****************************************************************************
Message packet group add
Group add message

Authored by Barry Durnin.
******************************************************************************/
#include "messagegroupadd.h"

MessageGroupAdd::MessageGroupAdd()
{
}

MessageGroupAdd::~MessageGroupAdd()
{
}

QByteArray MessageGroupAdd::CreateMessage(MessageBaseData* data)
{
	QByteArray str;
	MessageGroupAddData* groupData = static_cast<MessageGroupAddData*>(data);
	str.append(";Name=" + groupData->szName);
	str.append(";Members=");
	for (int i = 0; i < groupData->szMembers.size(); ++i)
	{
		str.append(groupData->szMembers[i]);
		str.append(" ");
	}
	str = MessageBase::CreateMessageTemplate(data->eType, str);
	return str;
}

bool MessageGroupAdd::VerifyMessage(const QByteArray& data)
{
	return false;
}

MessageBaseData* MessageGroupAdd::ReadMessage(const QByteArray& data)
{
	QStringList list;
	MessageGroupAddData* output = new MessageGroupAddData();

	QByteArrayList tmp = data.split(';');
	foreach(const QString &str, tmp)
	{
		if (str.contains("Name="))
		{
			list = str.split('=');
			if (list.length())
			{
				output->szName = list.takeAt(1);
			}
			continue;
		}
		else if (str.contains("Members="))
		{
			list = str.split('=');
			list.removeAt(0);
			if (list.length())
			{
				output->szMembers = list;
			}
			continue;
		}
	}

	return output;
}
