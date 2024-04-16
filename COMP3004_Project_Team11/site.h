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

        // treatment freq and ampl
        double treatFreqRoun1 = 0.0;  
        double treatFreqRound2 = 0.0;
        double treatFreqRound3 = 0.0;
        double treatFreqRound4 = 0.0;

        double treatAmplRound1 = 0.0;
        double treatAmplRound2 = 0.0;
        double treatAmplRound3 = 0.0;
        double treatAmplRound4 = 0.0;

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

        double getTreatFreqRound1() { return treatFreqRoun1; }
        double getTreatFreqRound2() { return treatFreqRound2; }
        double getTreatFreqRound3() { return treatFreqRound3; }
        double getTreatFreqRound4() { return treatFreqRound4; }

        double getTreatAmplRound1() { return treatAmplRound1; }
        double getTreatAmplRound2() { return treatAmplRound2; }
        double getTreatAmplRound3() { return treatAmplRound3; }
        double getTreatAmplRound4() { return treatAmplRound4; }

        void setTreatFreqRound1(double freq) { treatFreqRoun1 = freq; }
        void setTreatFreqRound2(double freq) { treatFreqRound2 = freq; }
        void setTreatFreqRound3(double freq) { treatFreqRound3 = freq; }
        void setTreatFreqRound4(double freq) { treatFreqRound4 = freq; }

        void readSignal(); 
        double getDominantFrequency();
        void genTreatmentAmpl(int round);
        void setTreatmentFreq(int round, double freq);
        void resetSite();

    private:
        void generateSignal();

};

#endif // SITE_H





