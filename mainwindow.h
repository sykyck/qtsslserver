#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QObject>
#include <QSslConfiguration>
#include "qsslserver.h"

class MainWindow : public QObject
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
signals:

public slots:

private:
    QSslServer *server;
};

#endif // MAINWINDOW_H
