#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
   server = new QSslServer(this);
   QSslConfiguration sslConfig;
}

MainWindow::~MainWindow()
{
   delete this->server;
}
