#include "mainwindow.h"
#include "device.h"
#include <QDate>
#include <QObject>
#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w; 
    w.show();

    
    return a.exec();
}
