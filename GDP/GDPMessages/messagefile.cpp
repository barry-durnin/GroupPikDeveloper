#include "messagefile.h"

MessageFile::MessageFile()
{
}

MessageFile::~MessageFile()
{
}

QByteArray MessageFile::CreateMessage(MessageBaseData* data)
{
	QByteArray str;
	MessageFileData* fileData = static_cast<MessageFileData*>(data);
	str.append(fileData->szFile);

	str = MessageBase::CreateMessageTemplate(file, str);
	return str;
}

bool MessageFile::VerifyMessage(const QByteArrayList& data)
{
	return true;
}

MessageBaseData* MessageFile::ReadMessage(const QByteArrayList& data)
{
	QStringList list;
	MessageFileData* output = new MessageFileData();

	foreach(const QByteArray &str, data)
	{
		output->szFile.append(str);
	}
	return output;
}