/*****************************************************************************
Message packet file
File message as byte array

Authored by Barry Durnin.
******************************************************************************/
#ifndef __MESSAGEFILE_H__
#define __MESSAGEFILE_H__

#include "messagebase.h"

#include <QFile>
#include <QIODevice>

struct MessageFileData : public MessageBaseData
{
	MessageFileData()
	{
		eType = file;
		szFile = "";
	}

	MessageFileData(const QString& dirFile)
	{
		eType = file;
		szFile = "";
		QFile file(dirFile);

		if (file.open(QIODevice::ReadOnly | QIODevice::Text | QIODevice::NotOpen | QIODevice::Append | QIODevice::Unbuffered | QIODevice::Truncate))
		{
			szFile = file.readAll();
		}
	}

	MessageFileData(const QByteArray& fileBytes)
	{
		eType = file;
		szFile = fileBytes;
	}
	QByteArray szFile;
};

class MessageFile : public MessageBase
{
private:
	friend class GDPMessages;
	MessageFile();
	QByteArray CreateMessage(MessageBaseData* data);
	bool VerifyMessage(const QByteArray& data);
	MessageBaseData* ReadMessage(const QByteArray& data);
public:
	~MessageFile();
};

#endif //__MESSAGEFILE_H__