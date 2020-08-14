#ifndef UPDATASERVER_H
#define UPDATASERVER_H

#include <QObject>
#include <QTcpServer>
#include "updataserverthread.h"

class UpdataServer : public QTcpServer
{
    Q_OBJECT;
public:
    UpdataServer(QObject *parent = nullptr);
public slots:
    void writeCommand(QByteArray);
protected:
    void incomingConnection(qintptr socketDescriptor) override;
private:
    UpdataServerThread *thread;
};

#endif // UPDATASERVER_H
