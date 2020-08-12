#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::init()
{
    userver = new UpdataServer();
    if(!userver->listen(QHostAddress::Any,8888)){
        QMessageBox::critical(this,
                              tr("Updata Server"),
                              tr("Unable to start the server: %1.").
                              arg(userver->errorString()));
        close();
        return;
    }else{
        qDebug()<<"updataserver is Listening on 8888";
    }
}

void MainWindow::on_pushButton_clicked()
{
    QString str = "{\"timestamp\":"+QString::number(QDateTime::currentSecsSinceEpoch())+"}\r\n";
    QByteArray data = str.toUtf8();
    userver->writeCommand(data);
}
