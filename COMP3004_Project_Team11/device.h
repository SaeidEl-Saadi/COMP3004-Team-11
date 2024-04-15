#ifndef DEVICE_H
#define DEVICE_H

#include <QObject>
#include <QVector>
#include <QDateTime>
#include <QDebug>
#include "site.h"
#include "session.h"
#include "signalgenprocess.h"
#include "freqband.h"
//#include "mainwindow.h"

class MainWindow;

class Device : public QObject {
    Q_OBJECT
    
    // attributes
    private:
        QVector<Site*> sites;
        QVector<Session*> sessions; 
        QDateTime datetime; // current date and time by the user
        QDateTime actualTimeSet; // real current system time when the device is set
        MainWindow* mainWindow;
        int numSites;

    // methods
    public:
        // constructor
        Device(int numSites, MainWindow* ui, QObject *parent = nullptr);

        //setters and getters
        QVector<Site*> getSites() { return sites; }
        QVector<Session*> getSessions() { return sessions; }
        QDateTime getCurrentDateTime();
        QDateTime getDateTime() { return datetime; }
        void setDateTime(QDateTime datetime);

        bool startNewSession();
        double getBaseLine();
        FreqBand getFreqBand(double fd);
        QString getFreqBandString(FreqBand band);

        void addOffset(FreqBand band, double offset, Site* site);
        void deleteLatestSession();
    private:
        void printToGUI(QString message);

};

#endif // DEVICE_H