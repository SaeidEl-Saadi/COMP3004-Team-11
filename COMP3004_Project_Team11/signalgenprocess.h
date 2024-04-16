#ifndef SIGNALGENPROCESS_H
#define SIGNALGENPROCESS_H

#include <QtCharts>
#include <random>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

class SignalGenProcess {
    public:
        SignalGenProcess(double duration, double sampleRate) : duration(duration), sampleRate(sampleRate) {};
        QLineSeries* generate(double alphaFreq, double alphaAmp, double betaFreq, double betaAmp, 
                                double deltaFreq, double deltaAmp, double thetaFreq, double thetaAmp, 
                                double treatFreqRoun1, double treatAmplRound1, double treatFreqRound2, double treatAmplRound2, 
                                double treatFreqRound3, double treatAmplRound3, double treatFreqRound4, double treatAmplRound4);
                                
        double calculateDominantFrequency(double f1, double A1, double f2, double A2, double f3, double A3, double f4, double A4,double f5,double A5,double f6,double A6,double f7,double A7,double f8, double A8);

    private:
        int duration;
        int sampleRate;
};

#endif // SIGNALGENPROCESS_H
