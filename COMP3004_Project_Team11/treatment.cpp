#include "treatment.h"

// Constructor for the Treatment class.
Treatment::Treatment(QObject *parent)
    : QObject(parent) {}

// Function to calculate the average frequency of a given signal.
double Treatment::calculateAverageFrequency( std::vector<double>& signal, double sampleRate) {
    // Create an instance of the ProcessSignal class
    ProcessSignal processSignal;

    // Perform FFT on the signal to obtain frequency domain representation
    std::vector<std::complex<double>> fftResult = processSignal.performFFT(signal);

    // Calculate the average frequency using the power spectral density method
    return processSignal.calculateAverageFrequencyUsingPSD(fftResult, sampleRate);
}

// Function to apply treatment to the original signal.
std::vector<double> Treatment::applyTreatment( std::vector<double>& originalSignal, double sampleRate) {
    // Create an instance of the ProcessSignal class
    ProcessSignal processSignal;

    // Initialize the new signal vector with the original signal
    std::vector<double> newSignal = originalSignal;

    // Repeat the treatment process 16 times
    for (int i = 0; i < 16; ++i) {
        // Calculate the average frequency of the current signal
        double avgFrequency = calculateAverageFrequency(newSignal, sampleRate);

        // Define the offset frequency (5Hz) from the average frequency
        double offsetFrequency = avgFrequency + 5.0;

        // Generate a sine wave with the offset frequency
        std::vector<double> treatmentWave = generateSineWave(offsetFrequency, originalSignal.size(), sampleRate);

        // Add the treatment wave to the new signal
        for (size_t j = 0; j < originalSignal.size(); ++j) {
            newSignal[j] += treatmentWave[j];
        }
    }

    return newSignal;
}

// Function to generate a sine wave with a specified frequency, duration, and sample rate.
std::vector<double> Treatment::generateSineWave(double frequency, size_t duration, double sampleRate) {
    std::vector<double> sineWave(duration, 0.0);

    for (size_t i = 0; i < duration; ++i) {
        double time = static_cast<double>(i) / sampleRate;
        sineWave[i] = std::sin(2.0 * M_PI * frequency * time);
    }

    return sineWave;
}
