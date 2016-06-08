#ifndef MESSAGELOGIN_H
#define MESSAGELOGIN_H

#include "messagebase.h"

struct MessageLoginData : public MessageBaseData
{
	MessageLoginData()
	{
		eType = login;
		szUser = "\0";
		szPass = "\0";
	}
    MessageLoginData(const QString& user, const QString& pass)
    {
        eType = login;
        szUser = user;
        szPass = pass;
    }
    QString szUser;
    QString szPass;
};

class MessageLogin : public MessageBase
{
private:
    friend class GDPMessages;
    MessageLogin();
	QString CreateMessage(MessageBaseData* data);
    bool VerifyMessage(const QString& data);
	MessageBaseData ReadMessage(const QStringList& data);
public:
    ~MessageLogin();
};

#endif // MESSAGELOGIN_H
