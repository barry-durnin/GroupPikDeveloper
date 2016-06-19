/*****************************************************************************
Message packet login
Login data message

Authored by Barry Durnin.
******************************************************************************/
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
    bool VerifyMessage(const QByteArray& data);
	MessageBaseData* ReadMessage(const QByteArray& data);
public:
    ~MessageLogin();
};

#endif // MESSAGELOGIN_H
