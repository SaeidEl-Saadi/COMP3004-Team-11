#include "brainwavegenerator.h"
#include <cmath>
#include <random>

// Constructor for the BrainWaveGenerator class.
// Initializes the generator with the provided sample rate, duration, brain region, seed control, and parent object.
BrainWaveGenerator::BrainWaveGenerator(int sampleRate, int duration, BrainRegion region, bool fixedSeed, QObject *parent)
    : QObject(parent), sampleRate(sampleRate), duration(duration), prominentRegion(region), fixedSeed(fixedSeed) {
    // Initialize the seed for random number generation. Use a fixed seed for reproducibility if fixedSeed is true, otherwise use a random seed.
    seed = fixedSeed ? 42 : std::random_device{}();
}

// Generates a simulated brainwave signal based on the configuration of the generator.
std::vector<double> BrainWaveGenerator::generate() {
    std::mt19937 gen(seed); // Mersenne Twister: Good quality random number generator
    std::vector<double> brainWave(sampleRate * duration, 0.0); // Initialize the brainwave vector with zeros

    // Distribution objects for generating random amplitudes, frequencies, and phases
    std::uniform_real_distribution<> amp_dist(0.5, 1.0); // For amplitude variation
    std::uniform_real_distribution<> freq_dist(0.8, 1.2); // For frequency variation
    std::uniform_real_distribution<> phase_dist(0, 2 * M_PI); // For phase variation
    std::normal_distribution<> noise_dist(0, 0.1); // For adding Gaussian noise

    // Base frequencies for the EEG bands in Hz
    double deltaFreq = 3.0; // Delta (0.5-4 Hz)
    double thetaFreq = 6.0; // Theta (4-8 Hz)
    double alphaFreq = 10.0; // Alpha (8-12 Hz)
    double betaFreq = 18.0; // Beta (12-30 Hz)
    double gammaFreq = 35.0; // Gamma (30-100 Hz)

    // Initial amplitudes for the EEG bands, potentially adjusted below
    double deltaAmp = amp_dist(gen);
    double thetaAmp = amp_dist(gen);
    double alphaAmp = amp_dist(gen);
    double betaAmp = amp_dist(gen);
    double gammaAmp = amp_dist(gen);

    // Adjust the amplitude for the specified prominent brain region to simulate focus on that frequency band
    switch (prominentRegion) {
        case Delta:
            deltaAmp *= 2.0; // Double the amplitude for Delta waves
            break;
        case Theta:
            thetaAmp *= 2.0; // Double the amplitude for Theta waves
            break;
        case Alpha:
            alphaAmp *= 2.0; // Double the amplitude for Alpha waves
            break;
        case Beta:
            betaAmp *= 2.0; // Double the amplitude for Beta waves
            break;
        case Gamma:
            gammaAmp *= 2.0; // Double the amplitude for Gamma waves
            break;
    }

    // Generate the brainwave signal by adding sine waves for each EEG band with the calculated amplitude, frequency, and phase
    for (size_t i = 0; i < brainWave.size(); ++i) {
        double time = static_cast<double>(i) / sampleRate; // Calculate the time in seconds for this sample
        // Add the contribution of each brainwave band
        brainWave[i] += deltaAmp * std::sin(2.0 * M_PI * deltaFreq * time + phase_dist(gen));
        brainWave[i] += thetaAmp * std::sin(2.0 * M_PI * thetaFreq * time + phase_dist(gen));
        brainWave[i] += alphaAmp * std::sin(2.0 * M_PI * alphaFreq * time + phase_dist(gen));
        brainWave[i] += betaAmp * std::sin(2.0 * M_PI * betaFreq * time + phase_dist(gen));
        brainWave[i] += gammaAmp * std::sin(2.0 * M_PI * gammaFreq * time + phase_dist(gen));

        // Add Gaussian noise to the signal
        brainWave[i] += noise_dist(gen);
    }

    emit newSignalGenerated(brainWave); // Emit a signal indicating a new brainwave signal has been generated
    return brainWave; // Return the generated brainwave signal
}
