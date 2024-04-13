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
        QLineSeries* currSignal;

        // frequency bands
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
        Site(SignalGenProcess* generator, double alphaFreq, double betaFreq, double deltaFreq, double thetaFreq, double alphaAmp, double betaAmp, double deltaAmp, double thetaAmp);

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

        
        void readSignal(); 
        double getDominantFrequency();

    private:
        void generateSignal();

};

#endif // SITE_H





