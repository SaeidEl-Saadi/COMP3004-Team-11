#ifndef SIGNALGENPROCESS_H
#define SIGNALGENPROCESS_H

#include <QtCharts>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

class SignalGenProcess {
    public:
        SignalGenProcess(double duration, double sampleRate) : duration(duration), sampleRate(sampleRate) {};
        QLineSeries* generate(double alphaFreq, double alphaAmp, double betaFreq, double betaAmp, double deltaFreq, double deltaAmp, double thetaFreq, double thetaAmp);
        double calculateDominantFrequency(double f1, double A1, double f2, double A2, double f3, double A3, double f4, double A4);

    private:
        double duration;
        double sampleRate;
};

#endif // SIGNALGENPROCESS_H
