#include <QApplication>
#include <QMainWindow>
#include <QObject>
#include "qsslserver.h"
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QGuiApplication a(argc, argv);
    MainWindow window;
    return a.exec();
}
