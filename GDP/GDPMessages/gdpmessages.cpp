#include "gdpmessages.h"

#include "messagebase.h"
#include "messagefail.h"
#include "messagefile.h"
#include "messagelogin.h"
#include "messagesuccess.h"

GDPMessages::GDPMessages()
{
	m_mapMessages[success] = new MessageSuccess();
	m_mapMessages[fail] = new MessageFail();
	m_mapMessages[login] = new MessageLogin();
	m_mapMessages[file] = new MessageFile();
}

GDPMessages::~GDPMessages()
{
	qDeleteAll(m_mapMessages);
	m_mapMessages.clear();
}

bool GDPMessages::CreateMessage(QByteArray& output, MessageBaseData* data)
{
	if (!data)
	{
		return false;
	}
	if(m_mapMessages.find(data->eType) != m_mapMessages.end())
	{
		Q_ASSERT(m_mapMessages[data->eType]);
		output = m_mapMessages[data->eType]->CreateMessage(data);
		return true;
	}
	return false;
}

bool GDPMessages::VerifyMessage(const QString& stream)
{
	if(stream.length())
	{

	}
	return false;
}

MessageBaseData* GDPMessages::ReadMessage(const QString& stream)
{
	if (stream.isEmpty())
	{
		//return false;
	}
	MessageBaseData* output; //replacing with callback system. temp holder for now testing work flow
	QStringList headerData;
	QStringList bodyData;
	MessageType type = max_message_type;

	headerData = stream.split("###");
	bodyData = headerData.takeLast().split(';');
	headerData = headerData.first().split(';');
	foreach(const QString &str, headerData)
	{
		
		if (str.contains("Type="))
		{
			type = (MessageType)str.split('=').last().toInt();
			break;
		}
	}
	
	if (type < max_message_type && type > unknown_message_type)
	{
		if (m_mapMessages.find(type) != m_mapMessages.end())
		{
			Q_ASSERT(m_mapMessages[type]);
			output = m_mapMessages[type]->ReadMessage(bodyData);
		}
	}

	return output;
}
