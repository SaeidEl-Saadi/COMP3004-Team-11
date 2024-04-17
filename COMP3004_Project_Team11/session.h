#ifndef SESSION_H
#define SESSION_H
#include "site.h"
#include <QDateTime>
#include <QObject>
#include <QVector>
#include <vector>


class Session : QObject {
    Q_OBJECT
    
    // attributes
    private:
        QDateTime datetime;
        bool hasUploaded = false;
        double avgBefore;
        double avgAfter;

        // first lvl is round, 2nd lvl signals of all 7 sites
        QVector<QVector<QLineSeries*>> roundSignals;  // 2D vector of QLineSeries

        // [round 1] = [site 1 signal, site 2 signal, site 3 signal, site 4 signal, site 5 signal, site 6 signal, site 7 signal]
        // [round 2] = [site 1 signal, site 2 signal, site 3 signal, site 4 signal, site 5 signal, site 6 signal, site 7 signal]
        // ....
        // [round 4] = [site 1 signal, site 2 signal, site 3 signal, site 4 signal, site 5 signal, site 6 signal, site 7 signal]

    // methods
    public:
        // constructor
        Session(int numSites, QDateTime datetime, QObject *parent = nullptr);
        ~Session() { deleteCharts(); }
        //setters and getters
        void setDate(QDateTime datetime) { this->datetime = datetime; }
        QDateTime getDateTime() { return datetime; }

        double getAvgBefore() { return avgBefore; }
        void setAvgBefore(double avgBefore) { this->avgBefore = avgBefore; }
        
        double getAvgAfter() { return avgAfter; }
        void setAvgAfter(double avgAfter) { this->avgAfter = avgAfter; }

        bool getHasUploaded(){ return hasUploaded; }
        void setHasUploaded(bool flag){ hasUploaded = flag; }

        QVector<QVector<QLineSeries*>> getRoundSignals() { return roundSignals; }
        void setRoundSignal(int round, int site, QLineSeries* signal) { roundSignals[round][site] = signal; }
        void deleteCharts();
};

#endif