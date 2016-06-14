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
	str.append("HeaderStart");
	str.append(";Type=" + QString::number(data->eType));
	str.append(";HeaderFinish;###");
	str.append(";BodyStart");
	str.append(";User=" + loginData->szUser);
	str.append(";Pass=" + loginData->szPass);
	str.append(";BodyFinish;\0");
	return str;
}

bool MessageLogin::VerifyMessage(const QString& data)
{
    return false;
}

MessageBaseData* MessageLogin::ReadMessage(const QStringList& data)
{
	QStringList list;
	MessageLoginData* output = new MessageLoginData();
	foreach(const QString &str, data)
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
