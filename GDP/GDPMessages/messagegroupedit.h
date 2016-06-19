/*****************************************************************************
Message packet group edit
Group edit message

Authored by Barry Durnin.
******************************************************************************/
#ifndef __MESSAGEGROUPEDIT_H__
#define __MESSAGEGROUPEDIT_H__

#include "messagebase.h"

#include <QStringList>

struct MessageGroupEditData : public MessageBaseData
{
	MessageGroupEditData()
	{
		eType = group_edit;
		szName = "\0";
		szNewName = "\0";
	}
	MessageGroupEditData(const QString& name, const QString& new_name, const QStringList& members) : MessageGroupEditData()
	{
		szName = name;
		szNewName = new_name;
		szMembers = members;
	}
	QString szName;
	QString szNewName;
	QStringList szMembers;
};

class MessageGroupEdit : public MessageBase
{
	friend class GDPMessages;
	MessageGroupEdit();
	QByteArray CreateMessage(MessageBaseData* data);
	bool VerifyMessage(const QByteArray& data);
	MessageBaseData* ReadMessage(const QByteArray& data);
public:
	~MessageGroupEdit();
};

#endif