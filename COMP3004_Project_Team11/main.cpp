#include "mainwindow.h"
#include "session.h"
#include <QDate>
#include <QObject>
#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // MainWindow w;
    // w.show();

    QDate date = QDate::currentDate();
    Session aSes = Session(date);
    aSes.readSignal();
    for (Site site : aSes.sites){
        QVector<double> signal = site.getSignal();
        for (double val : signal){
            qDebug() << val;
        }
    }

    return a.exec();
}
