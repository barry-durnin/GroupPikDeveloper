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
	str.append("HeaderStart");
	str.append(";Type=" + QString::number(data->eType));
	str.append(";HeaderFinish;###");
	str.append("BodyStart");
	str.append(";File=" + fileData->szFile);
	str.append(";BodyFinish;");
	return str;
}

bool MessageFile::VerifyMessage(const QString& data)
{
	return true;
}

MessageBaseData* MessageFile::ReadMessage(const QStringList& data)
{
	QStringList list;
	MessageFileData* output = new MessageFileData();
	foreach(const QString &str, data)
	{
		if (str.contains("File="))
		{
			list = str.split('=');
			if (list.length())
			{
				output->szFile = list.takeAt(1).toUtf8();
			}
			break;
		}
	}

	return output;
}