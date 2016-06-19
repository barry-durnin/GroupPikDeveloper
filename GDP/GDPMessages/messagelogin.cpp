/*****************************************************************************
Message packet login
Login data message

Authored by Barry Durnin.
******************************************************************************/
#include "messagelogin.h"

#include <QStringList>

MessageLogin::MessageLogin() : MessageBase()
{

}

MessageLogin::~MessageLogin()
{

}

QByteArray MessageLogin::CreateMessage(MessageBaseData* data)
{
	QByteArray str;
	MessageLoginData* loginData = static_cast<MessageLoginData*>(data);
	str.append(";User=" + loginData->szUser);
	str.append(";Pass=" + loginData->szPass);

	str = MessageBase::CreateMessageTemplate(login, str);
	return str;
}

bool MessageLogin::VerifyMessage(const QByteArray& data)
{
    return false;
}

MessageBaseData* MessageLogin::ReadMessage(const QByteArray& data)
{
	QStringList list;
	MessageLoginData* output = new MessageLoginData();

	QByteArrayList tmp = data.split(';');
	foreach(const QString &str, tmp)
	{
		if (str.contains("User="))
		{
			list = str.split('=');
			if (list.length())
			{
				output->szUser = list.takeAt(1);
			}
			continue;
		}
		else if (str.contains("Pass="))
		{
			list = str.split('=');
			if (list.length())
			{
				output->szPass = list.takeAt(1);
			}
			continue;
		}
	}

	return output;
}
