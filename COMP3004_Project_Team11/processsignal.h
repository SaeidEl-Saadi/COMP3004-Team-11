#ifndef PROCESSSIGNAL_H
#define PROCESSSIGNAL_H

#include <QObject>
#include <QDebug>
#include <complex>
#include <vector>
#include <cmath>

class ProcessSignal : public QObject {
    Q_OBJECT
    
    public:
        explicit ProcessSignal(QObject *parent = nullptr);
        static std::vector<double> calculateBaseline(const std::vector<std::vector<double>>& sigs);
        void applyFFT(std::vector<std::complex<double>>& data);
        std::vector<std::complex<double>> performFFT( std::vector<double>& realSignal);
        double calculateAverageFrequencyUsingPSD(const std::vector<std::complex<double>>& fftResult, double sampleRate);
        void printFFT( std::vector<std::complex<double>>& fftResult, double sampleRate);

    signals:

};

#endif // PROCESSSIGNAL_H
