// SignalGenerator.cpp

#include "signalgenerator.h"
#include <cmath>
#include <random>

SignalGenerator::SignalGenerator(QObject *parent) : QObject(parent) {
    // Constructor implementation if needed
}

QLineSeries* SignalGenerator::generateSignal(int sampleRate, int durationSeconds) {
    int numSamples = sampleRate * durationSeconds;
    double interval = 1.0 / sampleRate;

    const std::vector<FrequencyBand> brainwaveBands = {
        // ... Initialize your frequency bands here
    };

    // Random noise generator setup
    double noiseStdDev = 1.0; // Noise standard deviation
    std::default_random_engine generator;
    std::normal_distribution<double> distribution(0.0, noiseStdDev);

    QLineSeries *series = new QLineSeries();
    for (int i = 0; i < numSamples; ++i) {
        double x = i * interval; // Time in seconds
        double y = 0.0;
        for (const auto& band : brainwaveBands) {
            y += band.amplitude * std::sin(2 * M_PI * band.frequency * x);
        }

        // Generate band-limited noise by summing sinusoidal components
        double noise = distribution(generator); // Gaussian noise
        // Optionally add line noise simulation
        noise += 0.2 * std::sin(2 * M_PI * 50 * x); // Simulate 50 Hz line noise with low amplitude

        y += noise; // Add noise

        series->append(x / 60.0, y); // Convert x to minutes and keep y in µV
    }

    return series; // Return the generated signal series
}
