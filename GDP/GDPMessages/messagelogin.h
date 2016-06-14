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
	QByteArray CreateMessage(MessageBaseData* data);
    bool VerifyMessage(const QByteArrayList& data);
	MessageBaseData* ReadMessage(const QByteArrayList& data);
public:
    ~MessageLogin();
};

#endif // MESSAGELOGIN_H
