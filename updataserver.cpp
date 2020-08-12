#include "updataserver.h"

UpdataServer::UpdataServer(QObject *parent)
    : QTcpServer(parent)
{}

void UpdataServer::incomingConnection(qintptr socketDescriptor)
{
    UpdataServerThread *thread = new UpdataServerThread(socketDescriptor);
    connect(thread, &UpdataServerThread::finished, thread, &UpdataServerThread::deleteLater);
    connect(this, &UpdataServer::writeCommand, thread, &UpdataServerThread::sendCommand,Qt::DirectConnection);

    qDebug()<<"Connected client "<< socketDescriptor;

    thread->start();
}
