#ifndef UPDATASERVERTHREAD_H
#define UPDATASERVERTHREAD_H

#include <QObject>
#include <QThread>
#include <QTcpSocket>
#include <QtNetwork>

class UpdataServerThread : public QThread
{
    Q_OBJECT;
public:
    UpdataServerThread(int socketDescriptor, QObject *parent=nullptr);

    void run() override;

signals:
    void error(QTcpSocket::SocketError socketError);

public slots:
    void readyRead();
    void disconnected();
    void sendCommand(QByteArray);

private:
    int socketDescriptor;
    QTcpSocket *updata_socket;
    QHash<QHostAddress,QTcpSocket*> connected_client_socket;
    QHash<QHostAddress,QString> connected_client_ip;
};

#endif // UPDATASERVERTHREAD_H
