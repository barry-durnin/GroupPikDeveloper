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

bool MessageFile::VerifyMessage(const QByteArray& data)
{
	return true;
}

MessageBaseData* MessageFile::ReadMessage(const QByteArray& data)
{
	QStringList list;
	MessageFileData* output = new MessageFileData();

	output->szFile = data;

	return output;
}