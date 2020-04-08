#include "s2vnathread.h"
#include "scpicommands.h"

S2VNAThread::S2VNAThread(QTcpSocket *socket)
{
    _socket = socket;
}

void S2VNAThread::run()
{
    _socket->
    emit send();
}
