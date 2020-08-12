#include "updataserverthread.h"

UpdataServerThread::UpdataServerThread(int socketDescriptor, QObject *parent) : QThread(parent), socketDescriptor(socketDescriptor)
{
    updata_socket = new QTcpSocket();
    connect(updata_socket,SIGNAL(readyRead()),this,SLOT(readyRead()),Qt::QueuedConnection);
    connect(updata_socket,SIGNAL(disconnected()),this,SLOT(disconnected()),Qt::DirectConnection);
}

void UpdataServerThread::run()
{
    if (!updata_socket->setSocketDescriptor(socketDescriptor)) {
        emit error(updata_socket->error());
        return;
    }
    connected_client_socket.insert(updata_socket->peerAddress(),updata_socket);
    //connected with unique device
    //connected_client_ip.insert(updata_socket->peerAddress(),"TEST_DEVICE2");
    connected_client_ip.insert(updata_socket->peerAddress(),"TEST_DEVICE");

    exec();
}

void UpdataServerThread::disconnected()
{
    connected_client_socket.remove(updata_socket->peerAddress());
    connected_client_ip.remove(updata_socket->peerAddress());

    qDebug() << socketDescriptor << "disconnected";
    exit(0);
}

void UpdataServerThread::readyRead()
{
    qDebug()<<"connected_client_socket => "<<connected_client_socket;
    qDebug()<<"connected_client_ip => "<<connected_client_socket;

    QByteArray Data = updata_socket->readLine();
    QJsonDocument document = QJsonDocument::fromJson(Data.data());
    qDebug()<<updata_socket->peerAddress()<<"in : "<<Data.data();
}

void UpdataServerThread::sendCommand(QByteArray cmd)
{
    QString device = "TEST_DEVICE";
    QHostAddress deviceIp = connected_client_ip.key(device);
    ((QTcpSocket*)connected_client_socket.value(deviceIp))->write(cmd);
    ((QTcpSocket*)connected_client_socket.value(deviceIp))->waitForBytesWritten(5000);
    ((QTcpSocket*)connected_client_socket.value(deviceIp))->flush();
}

