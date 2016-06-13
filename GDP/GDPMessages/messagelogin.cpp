#include "messagelogin.h"

#include <QStringList>

MessageLogin::MessageLogin() : MessageBase()
{

}

MessageLogin::~MessageLogin()
{

}

QString MessageLogin::CreateMessage(MessageBaseData* data)
{
	QString str;
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
	MessageLoginData* output = new MessageLoginData();
	foreach(const QString &str, data)
	{
		if (str.contains("User="))
		{
			output->szUser = str.split('=').takeAt(1);
			continue;
		}
		else if (str.contains("Pass="))
		{
			output->szPass = str.split('=').takeAt(1);
			continue;
		}
	}

	return output;
}
