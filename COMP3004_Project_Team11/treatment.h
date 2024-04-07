#ifndef TREATMENT_H
#define TREATMENT_H

#include <QObject>
#include <vector>
#include <complex>
#include "processsignal.h" // Include header file for FFT functions

class Treatment : public QObject {
    Q_OBJECT

public:
    explicit Treatment(QObject *parent = nullptr);

    double calculateAverageFrequency( std::vector<double>& signal, double sampleRate);
    std::vector<double> applyTreatment( std::vector<double>& originalSignal, double sampleRate);

private:
    std::vector<double> generateSineWave(double frequency, size_t duration, double sampleRate);
};

#endif // TREATMENT_H
