#include "mainwindow.h"
#include "session.h"
#include "site.h"
#include <QDate>
#include <QObject>
#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
     MainWindow w;
     w.show();

    QDate date = QDate::currentDate();

    qDebug() << date;

    Session aSes(date);

    aSes.generateInitialSignals();

    // int i = 1;
    // for (Site *site : aSes.getSites()) {
    //     QVector<double> signal = site->getSignal();
    //     qDebug() << "Site: " << i;
    //     for (double val : signal){
    //         qDebug() << val;
    //     }
    //     i++;
    // }

    return a.exec();
}
