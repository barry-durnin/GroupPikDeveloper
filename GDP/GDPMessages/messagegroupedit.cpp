/*****************************************************************************
Message packet group edit
Group edit message

Authored by Barry Durnin.
******************************************************************************/

#include "messagegroupedit.h"

MessageGroupEdit::MessageGroupEdit()
{
}

MessageGroupEdit::~MessageGroupEdit()
{
}

QByteArray MessageGroupEdit::CreateMessage(MessageBaseData* data)
{
	QByteArray str;
	MessageGroupEditData* groupData = static_cast<MessageGroupEditData*>(data);
	str.append(";Name=" + groupData->szName);
	str.append(";NewName=" + groupData->szNewName);
	str.append(";Members=");
	for (int i = 0; i < groupData->szMembers.size(); ++i)
	{
		str.append(groupData->szMembers[i]);
		str.append(" ");
	}
	str = MessageBase::CreateMessageTemplate(data->eType, str);
	return str;
}

bool MessageGroupEdit::VerifyMessage(const QByteArray& data)
{
	return false;
}

MessageBaseData* MessageGroupEdit::ReadMessage(const QByteArray& data)
{
	QStringList list;
	MessageGroupEditData* output = new MessageGroupEditData();

	QByteArrayList tmp = data.split(';');
	foreach(const QString &str, tmp)
	{
		if (str.contains("NewName="))
		{
			list = str.split('=');
			if (list.length())
			{
				output->szNewName = list.takeAt(1);
			}
			continue;
		}
		else if (str.contains("Name="))
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

