#include "mainwindow.h"
#include "session.h"
#include "site.h"
#include "brainwavegenerator.h"
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



    // testing create a Site
    // BrainWaveGenerator* generator = new BrainWaveGenerator(256, 60, BrainRegion::Delta);
    // Site* site = new Site(generator);

    // testing create a Device, set date and time and start a new session
    // Device* device = new Device(10, 3);
    // QDateTime* date = new QDateTime(QDate(2021, 1, 1), QTime(11, 30, 0));
    // device->setDateTime(*date);
    // device->startNewSession();

    return a.exec();
}
