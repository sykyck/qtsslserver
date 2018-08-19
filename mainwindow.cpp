#include "mainwindow.h"
#include <QFile>
#include <QFileDialog>
#include <QSslKey>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
   server = new QSslServer(this);
   QSslConfiguration sslConfig;
   QList<QSslCertificate> certList = QSslCertificate::fromPath("./cert/replyserver.pem");
   sslConfig.setCaCertificates(certList);
   QFile *keyFileHandle = new QFile("./cert/replyserver.key", this);
   QSslKey key(keyFileHandle);
   sslConfig.setPrivateKey(key);
   QSslError error(QSslError::SelfSignedCertificate, certList.at(0));
   qDebug()<<error.errorString();
   QList<QSslError> expectedSslErrors;
   expectedSslErrors.append(error);
   server->setSslConfiguration(sslConfig);
   server->listen(QHostAddress("127.0.0.1"),1965);
   connect(server, SIGNAL(newConnection()), this, SLOT(onIncomingConnection()));
   connect(server, SIGNAL(acceptError(QAbstractSocket::SocketError)), this, SLOT(onAcceptError(QAbstractSocket::SocketError)));
}

void MainWindow::onIncomingConnection() {
    qDebug() << "MainWindow::onIncomingConnection: Receiving...";
    QSslSocket *socket = server->nextPendingConnection();
    socket->setSocketOption(QAbstractSocket::KeepAliveOption, true);
    connect(socket, SIGNAL(connected()), this, SLOT(onSocketConnected()));
    connect(socket, SIGNAL(encrypted()), this, SLOT(onEncrypted()));
    connect(socket, SIGNAL(stateChanged(QAbstractSocket::SocketState)), this, SLOT(onSocketStateChanged(QAbstractSocket::SocketState)));
    connect(socket, SIGNAL(sslErrors(QList<QSslError>)), this, SLOT(onSslErrors(QList<QSslError>)));
    connect(socket, SIGNAL(readyRead()), this, SLOT(onBytesReady()), Qt::UniqueConnection);
    connect(socket, SIGNAL(disconnected()), this, SLOT(onSocketDisconnect()));
    connect(socket, SIGNAL(peerVerifyError(QSslError)), this, SLOT(onPeerVerifyError(QSslError)));
}

MainWindow::~MainWindow()
{
}

void MainWindow::onAcceptError(QAbstractSocket::SocketError error) {
   qDebug()<<"MainWindow Server Socket onAccept Error= "<<error;
}

void MainWindow::onPeerVerifyError(QSslError error) {
   qDebug()<<"MainWindow Server Socket onAccept Error= "<<error.errorString();
}

void MainWindow::onSocketConnected() {
   qDebug()<<"MainWindow Server Socket Connection successfully established";
}

void MainWindow::onSocketDisconnect() {
   qDebug()<<"MainWindow Server Socket Disconnected ";
   QSslSocket *socket = qobject_cast<QSslSocket *>(sender());
   socket->deleteLater();
}

void MainWindow::onEncrypted() {
   qDebug()<<"MainWindow Server Socket has entered Encrypted mode";
}

void MainWindow::onSocketStateChanged(QAbstractSocket::SocketState state) {
   qDebug()<<"MainWindow Server Socket State Changed to = "<<state;
}

void MainWindow::onSslErrors(QList<QSslError> errorList) {
    foreach (QSslError error, errorList) {
        qDebug()<<error.errorString();
    }
}

void MainWindow::onBytesReady() {
    qDebug() << "MainWindow::onBytesReady: Processing request";
    if(!server->isListening())
    {
        return;
    }
    QSslSocket *socket = qobject_cast<QSslSocket *>(sender());
    if (!socket) {
        qWarning() << "MainWindow::onBytesReady: No socket available";
        return;
    }

    QByteArray data = socket->readAll();
    data.toStdString();
    qWarning()<<QString("Value of ByteArray= %1").arg(QString::fromUtf8(data));
    qDebug() << "MainWindow::onBytesReady: Query params found, closing server";
}
