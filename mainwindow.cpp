#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QObject(parent)
{
   server = new QSslServer(this);
   QSslConfiguration sslConfig;
   QList<QSslCertificate> certList = QSslCertificate::fromPath("./replyserver.pem");
   sslConfig.setCaCertificates(certList);
}

MainWindow::~MainWindow()
{
   delete this->server;
}
