#include "signalgenprocess.h"


QLineSeries* SignalGenProcess::generate(double alphaFreq, double alphaAmp, double betaFreq, double betaAmp, double deltaFreq, double deltaAmp, 
                                        double thetaFreq, double thetaAmp, double treatFreqRoun1, double treatAmplRound1, double treatFreqRound2, double treatAmplRound2, 
                                        double treatFreqRound3, double treatAmplRound3, double treatFreqRound4, double treatAmplRound4) {
    QLineSeries *series = new QLineSeries();
    
    for (int i = 0; i < sampleRate * duration; ++i) {
        float t = i / float(sampleRate);

        float alphaValue = alphaAmp * std::sin(2 * M_PI * alphaFreq * t);
        float betaValue = betaAmp * std::sin(2 * M_PI * betaFreq * t);
        float deltaValue = deltaAmp * std::sin(2 * M_PI * deltaFreq * t);
        float thetaValue =  thetaAmp * std::sin(2 * M_PI * thetaFreq * t);

        float treatValueRound1 = treatAmplRound1 * std::sin(2 * M_PI * treatFreqRoun1 * t);
        float treatValueRound2 = treatAmplRound2 * std::sin(2 * M_PI * treatFreqRound2 * t);
        float treatValueRound3 = treatAmplRound3 * std::sin(2 * M_PI * treatFreqRound3 * t);
        float treatValueRound4 = treatAmplRound4 * std::sin(2 * M_PI * treatFreqRound4 * t);
        
        float compositeValue = alphaValue + betaValue + deltaValue + thetaValue + treatValueRound1 + treatValueRound2 + treatValueRound3 + treatValueRound4;
        
        series->append(t, compositeValue);
    }

    return series;
}


double SignalGenProcess::calculateDominantFrequency(double f1, double A1, double f2, double A2, double f3, double A3, double f4, double A4,double f5,double A5,double f6,double A6,double f7,double A7,double f8, double A8) {
    double numerator = (f1 * pow(A1, 2)) + (f2 * pow(A2, 2)) + (f3 * pow(A3, 2)) + (f4 * pow(A4, 2)) + (f5*pow(A5,2)) + (f6*pow(A6,2)) + (f7*pow(A7,2)) + (f8*pow(A8,2));
    double denominator = pow(A1, 2) + pow(A2, 2) + pow(A3, 2) + pow(A4, 2) + pow(A5,2) + pow(A6,2) + pow(A7,2) + pow(A8,2);
    double fd = 0.0;

    if (denominator != 0) { 
        fd = numerator / denominator;
    }

    return fd;
}