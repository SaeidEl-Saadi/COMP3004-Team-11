#ifndef SITE_H
#define SITE_H

#include <QObject>
#include <QDebug>
#include <vector>
#include "signalgenprocess.h"

class Site : public QObject
{
    Q_OBJECT

    // attributes
    private:
        SignalGenProcess* generator;
        QLineSeries* currSignal = nullptr;

        // frequency bands: alpha [8-12Hz], beta [12-30Hz], delta [1-4Hz], theta [4-8Hz]
        double alphaFreq;
        double betaFreq;
        double deltaFreq;
        double thetaFreq;

        // amplitude bands
        double alphaAmp;
        double betaAmp;
        double deltaAmp;
        double thetaAmp;

    // methods
    public:
        Site(SignalGenProcess* generator);

        // getters and setters
        void setSignal(QLineSeries* signal) { currSignal = signal; }
        QLineSeries* getSignal() { return currSignal; }

        void addAlphaFreq(double offset) { this->alphaFreq += offset; }
        void addBetaFreq(double offset) { this->betaFreq += offset;}
        void addDeltaFreq(double offset) { this->deltaFreq += offset;}
        void addThetaFreq(double offset) { this->thetaFreq += offset; }

        double getAlphaFreq() { return alphaFreq; }
        double getBetaFreq() { return betaFreq; }
        double getDeltaFreq() { return deltaFreq; }
        double getThetaFreq() { return thetaFreq; }

        double getAlphaAmp() { return alphaAmp; }
        double getBetaAmp() { return betaAmp; }
        double getDeltaAmp() { return deltaAmp; }
        double getThetaAmp() { return thetaAmp; }

        
        void readSignal(); 
        double getDominantFrequency();
        void newAmp();
        void newFreq();

    private:
        void generateSignal();

};

#endif // SITE_H





