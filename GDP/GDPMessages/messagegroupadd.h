/*****************************************************************************
Message packet group add
Group add message

Authored by Barry Durnin.
******************************************************************************/
#ifndef __MESSAGEGROUPADDEDIT_H__
#define __MESSAGEGROUPADDEDIT_H__

#include "messagebase.h"

#include <QStringList>

struct MessageGroupAddData : public MessageBaseData
{
	MessageGroupAddData()
	{
		eType = group_add;
		szName = "\0";
	}
	MessageGroupAddData(const QString& name, const QStringList& members) : MessageGroupAddData()
	{
		szName = name;
		szMembers = members;
	}
	QString szName;
	QStringList szMembers;
};

class MessageGroupAdd : public MessageBase
{
private:
	friend class GDPMessages;
	MessageGroupAdd();
	QByteArray CreateMessage(MessageBaseData* data);
	bool VerifyMessage(const QByteArray& data);
	MessageBaseData* ReadMessage(const QByteArray& data);
public:
	~MessageGroupAdd();
};

#endif