/*****************************************************************************
Server entry point

Authored by Barry Durnin.
******************************************************************************/

#include <QCoreApplication>
#include "tcpserver.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    TcpServer server;
    return a.exec();
}
