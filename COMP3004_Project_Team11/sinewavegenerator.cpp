#include "sinewavegenerator.h"
#include <cmath>
#include <random>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

SineWaveGenerator::SineWaveGenerator(double sampleRate, double duration)
    : m_sampleRate(sampleRate), m_duration(duration) {}

std::vector<double> SineWaveGenerator::generate(double frequency) const {
    size_t samples = static_cast<size_t>(m_sampleRate * m_duration);
    std::vector<double> sineWave(samples);

    for (size_t i = 0; i < samples; ++i) {
        double t = i / m_sampleRate;
        sineWave[i] = std::sin(2.0 * M_PI * frequency * t);
    }

    return sineWave;
}

std::vector<double> SineWaveGenerator::generateComplex(double dominantFrequency) const {
    size_t samples = static_cast<size_t>(m_sampleRate * m_duration);
    std::vector<double> complexWave(samples);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 2.0 * M_PI);

    // Define relative frequencies based on the specified dominant frequency
    std::vector<std::pair<double, double>> frequencies = {
        {dominantFrequency * 0.05, 0.2}, // Delta
        {dominantFrequency * 0.25, 0.3}, // Theta
        {dominantFrequency * 0.5, 0.4},  // Alpha
        {dominantFrequency * 1.0, 0.5},  // Beta (central frequency)
        {dominantFrequency * 2.0, 0.6}   // Gamma
    };

    for (size_t i = 0; i < samples; ++i) {
        double t = i / m_sampleRate;
        complexWave[i] = 0;  // Initialize to zero before adding components
        for (const auto& [freq, amp] : frequencies) {
            double phase = dis(gen);  // Random phase for each component
            complexWave[i] += amp * std::sin(2.0 * M_PI * freq * t + phase);
        }
    }

    return complexWave;
}
