#include "signalgenprocess.h"


QLineSeries* SignalGenProcess::generate(double alphaFreq, double alphaAmp, double betaFreq, double betaAmp, double deltaFreq, double deltaAmp, double thetaFreq, double thetaAmp) {
    QLineSeries *series = new QLineSeries();
    
    for (int i = 0; i < sampleRate * duration; ++i) {
        float t = i / float(sampleRate);

        float alphaValue = alphaAmp * std::sin(2 * M_PI * alphaFreq * t);
        float betaValue = betaAmp * std::sin(2 * M_PI * betaFreq * t);
        float deltaValue = deltaAmp * std::sin(2 * M_PI * deltaFreq * t);
        float thetaValue =  thetaAmp * std::sin(2 * M_PI * thetaFreq * t);

        float compositeValue = alphaValue + betaValue + deltaValue + thetaValue;
        series->append(t, compositeValue);
    }

    return series;
}


double SignalGenProcess::calculateDominantFrequency(double f1, double A1, double f2, double A2, double f3, double A3, double f4, double A4) {
    double numerator = (f1 * pow(A1, 2)) + (f2 * pow(A2, 2)) + (f3 * pow(A3, 2)) + (f4 * pow(A4, 2));
    double denominator = pow(A1, 2) + pow(A2, 2) + pow(A3, 2) + pow(A4, 2);
    double fd = 0.0;

    if (denominator != 0) { 
        fd = numerator / denominator;
    }

    return fd;
}

