#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QObject>
#include <QDebug>
#include <QSslConfiguration>
#include "qsslserver.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
signals:

public slots:
    void onSocketConnected();
    void onSocketDisconnect();
    void onEncrypted();
    void onSocketStateChanged(QAbstractSocket::SocketState state);
    void onAcceptError(QAbstractSocket::SocketError error);
    void onPeerVerifyError(QSslError error);
    void onSslErrors(QList<QSslError> errorList);
    void onBytesReady();
    void onIncomingConnection();

private:
    QSslServer *server;
};

#endif // MAINWINDOW_H
