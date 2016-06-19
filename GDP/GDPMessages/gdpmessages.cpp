/*****************************************************************************
Message library manager

Generates message data packets
Reads message data packets

Authored by Barry Durnin.
******************************************************************************/

#include "gdpmessages.h"

#include "messagebase.h"
#include "messagefail.h"
#include "messagefile.h"
#include "messagegroupadd.h"
#include "messagegroupedit.h"
#include "messagelogin.h"
#include "messagesuccess.h"

GDPMessages::GDPMessages()
{
	m_mapMessages[success] = new MessageSuccess();
	m_mapMessages[fail] = new MessageFail();
	m_mapMessages[login] = new MessageLogin();
	m_mapMessages[file] = new MessageFile();
	m_mapMessages[group_add] = new MessageGroupAdd();
	m_mapMessages[group_edit] = new MessageGroupEdit();
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

bool GDPMessages::VerifyMessage(const QByteArray& stream)
{
	if(stream.length())
	{

	}
	return false;
}

unsigned int GDPMessages::GetMessageSize(const QByteArray& stream)
{
	if (stream.isEmpty())
	{
		//return false;
	}
	unsigned int size = 0;
	QByteArrayList headerData;
	
	headerData = stream.split(char('#'));
	headerData = headerData.first().split(';');
	foreach(const QString &str, headerData)
	{
		if (str.contains("Size="))
		{
			QString tmp = str.split('=').last();
			tmp = tmp.split('*').first();
			size = tmp.toInt();
			break;
		}
	}
	return size;
}

MessageBaseData* GDPMessages::ReadMessage(const QByteArray& stream)
{
	if (stream.isEmpty())
	{
		//return false;
	}
	MessageBaseData* output; //replacing with callback system. temp holder for now testing work flow
	QByteArrayList headerData;
	QByteArray bodyData;
	MessageType type = max_message_type;

	headerData = stream.split(char('#'));
	int size = headerData.first().size() + 1;
	
	bodyData = stream.right(stream.size() - size);


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
