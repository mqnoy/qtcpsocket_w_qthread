#include "updataserverthread.h"

UpdataServerThread::UpdataServerThread(int socketDescriptor, QObject *parent) : QThread(parent), socketDescriptor(socketDescriptor)
{}

void UpdataServerThread::run()
{
    updata_socket = new QTcpSocket();
    if (!updata_socket->setSocketDescriptor(socketDescriptor)) {
        emit error(updata_socket->error());
        return;
    }

    connect(updata_socket,SIGNAL(readyRead()),this,SLOT(readyRead()));
    connect(updata_socket,SIGNAL(disconnected()),this,SLOT(disconnected()));

    connected_client_socket.insert(updata_socket->peerAddress(),updata_socket);
    qDebug()<<"creating socket ptr";

    updata_socket->write("Welecome Message");
    qDebug()<<"UpdataServerThread::run() => current thread :"<<QThread::currentThread();

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
    qDebug()<<updata_socket;
    qDebug()<<"connected_client_socket => "<<connected_client_socket;
    qDebug()<<"connected_client_ip => "<<connected_client_ip;

    QByteArray Data = updata_socket->readLine();
    QJsonDocument document = QJsonDocument::fromJson(Data.data());
    QJsonObject object = document.object();

    //qDebug()<<"current thread :"<<QThread::currentThread()<<" DEVICE::"<<updata_socket->peerAddress()<<"in : "<<Data.data();

    //authorize device
    if(Data.contains("devNumber")){
        connected_client_ip.insert(updata_socket->peerAddress(),object.value("devNumber").toString());
        QString str = "{\"msg\":\"Device registered successfully.\",\"timestamp\":"+QString::number(QDateTime::currentSecsSinceEpoch())+"}";
        QByteArray registered_device = str.toUtf8();

        ((QTcpSocket*)connected_client_socket.value(updata_socket->peerAddress()))->write(registered_device);

    }
    qDebug()<<"connected_client_ip::"<<connected_client_ip;
}

void UpdataServerThread::sendCommand(QByteArray cmd)
{

    //    qDebug()<<"connected_client_ip::"<<connected_client_ip;
    qDebug()<<"UpdataServerThread::sendCommand::"<<cmd;

    //    QString device = "TEST123";
    //    QHostAddress deviceIp = connected_client_ip.key(device);

    //    qDebug()<<"deviceIp => "<<deviceIp;

    //    ((QTcpSocket*)connected_client_socket.value(deviceIp))->write(cmd);
    //    ((QTcpSocket*)connected_client_socket.value(deviceIp))->waitForBytesWritten(5000);
    //    ((QTcpSocket*)connected_client_socket.value(deviceIp))->flush();
}

