#include "session.h"

Session::Session(int numSites, QDateTime datetime, QObject *parent) : QObject(parent), datetime(datetime) {
    // initilize roundSignals to nullptr
    for (int i = 0; i < 5; i++){
        QVector<QLineSeries*> round;
        for (int j = 0; j < numSites; j++){
            round.push_back(nullptr);
        }
        roundSignals.push_back(round);
    }
}


void Session::deleteCharts() {
    // delete the last session
    for (int i = 0; i < roundSignals.size(); i++){
        for (int j = 0; j < roundSignals[i].size(); j++){
            if (roundSignals[i][j] != nullptr)
                delete roundSignals[i][j];
        }
    }
}