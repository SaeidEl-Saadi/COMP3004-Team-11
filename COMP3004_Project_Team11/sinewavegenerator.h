// SineWaveGenerator.h
#ifndef SINEWAVEGENERATOR_H
#define SINEWAVEGENERATOR_H

#include <vector>

class SineWaveGenerator {
public:
    SineWaveGenerator(double sampleRate, double duration);

    std::vector<double> generate(double frequency) const;
    std::vector<double> generateComplex(double dominantFrequency) const;

private:
    double m_sampleRate;
    double m_duration;
};

#endif // SINEWAVEGENERATOR_H
