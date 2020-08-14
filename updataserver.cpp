#include "updataserver.h"

UpdataServer::UpdataServer(QObject *parent)
    : QTcpServer(parent)
{}

void UpdataServer::incomingConnection(qintptr socketDescriptor)
{
    thread = new UpdataServerThread(socketDescriptor);
    connect(thread, &UpdataServerThread::finished, thread, &UpdataServerThread::deleteLater);

    qDebug()<<"Connected client "<< socketDescriptor;
    thread->start();
}

void UpdataServer::writeCommand(QByteArray command){
    thread->sendCommand(command);
}
