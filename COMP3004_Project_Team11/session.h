#ifndef SESSION_H
#define SESSION_H
#include "site.h"
#include "brainwavegenerator.h"
#include "brainregion.h"
#include <QDateTime>
#include <QObject>
#include <QVector>
#include <vector>


class Session : QObject {
    Q_OBJECT
    
    // attributes
    private:
        QDateTime datetime;
        std::vector<double> avgBefore;
        std::vector<double> avgAfter;

    // methods
    public:
        // constructor
        Session(QDateTime datetime, QObject *parent = nullptr);

        //setters and getters
        void setDate(QDateTime datetime) { this->datetime = datetime; }
        QDateTime getDate() { return datetime; }

        std::vector<double> getAvgBefore() { return avgBefore; }
        void setAvgBefore(std::vector<double> avgBefore) { this->avgBefore = avgBefore; }
        
        std::vector<double> getAvgAfter() { return avgAfter; }
        void setAvgAfter(std::vector<double> avgAfter) { this->avgAfter = avgAfter; }
    
    private:



    // signals:

    // public slots:

};

#endif
