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
signals:
    void writeCommand(QByteArray);
protected:
    void incomingConnection(qintptr socketDescriptor) override;

};

#endif // UPDATASERVER_H
