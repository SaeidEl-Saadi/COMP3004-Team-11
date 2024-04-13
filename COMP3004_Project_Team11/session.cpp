#include "session.h"

Session::Session(int numSites, QDateTime datetime, QObject *parent) : QObject(parent), datetime(datetime) {
    // initilize roundSignals to nullptr
    for (int i = 0; i < 4; i++){
        QVector<QLineSeries*> round;
        for (int j = 0; j < numSites; j++){
            round.push_back(nullptr);
        }
        roundSignals.push_back(round);
    }
}