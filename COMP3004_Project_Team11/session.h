#ifndef SESSION_H
#define SESSION_H
#include "site.h"
#include <QDate>
#include <QObject>
#include <QVector>
#include "brainwavegenerator.h"
#include <vector>
#include <iostream>

class Session : QObject {
    Q_OBJECT
    
    private:
        QVector<Site*> sites;
        QDate date; // date and time it starts
        QVector<double> avgBefore;
        QVector<double> avgAfter;
        BrainWaveGenerator* generator;

    public:
        Session(QDate date, QObject *parent = nullptr);
        void setDate(QDate date);
        QVector<Site*> getSites();
        QDate getDate();
        void readSignal(); // read the signals from the sites
        void generateInitialSignals();
        enum BrainRegion { Delta, Theta, Alpha, Beta, Gamma };
    private:
//        void readSignal(); // read the signals from the sites



    // signals:

    // public slots:

};

#endif
