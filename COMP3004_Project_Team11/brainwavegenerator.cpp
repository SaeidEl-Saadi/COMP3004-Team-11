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

    // Distribution objects for generating random amplitudes and phases
    std::uniform_real_distribution<> amp_dist(0.5, 1.0); // For amplitude variation
    std::uniform_real_distribution<> phase_dist(0, 2 * M_PI); // For phase variation
    std::normal_distribution<> noise_dist(0, 0.05); // Adjusted noise level

    // Calculate the average frequencies for each EEG band
    double deltaFreq = (0.1 + 3.0) / 2; // Average Delta frequency
    double thetaFreq = (3.5 + 7.5) / 2; // Average Theta frequency
    double alphaFreq = (7.5 + 13.0) / 2; // Average Alpha frequency
    double betaFreq = (14.0 + 30.0) / 2; // Average Beta frequency
    double gammaFreq = (30.0 + 80.0) / 2; // Average Gamma frequency

    // Generate the brainwave signal by adding sine waves for each EEG band with the calculated amplitude, frequency, and phase
    for (size_t i = 0; i < brainWave.size(); ++i) {
        double time = static_cast<double>(i) / sampleRate;

        // Iterate through each brainwave band
        double frequencies[] = {deltaFreq, thetaFreq, alphaFreq, betaFreq, gammaFreq};
        BrainRegion regions[] = {BrainRegion::Delta, BrainRegion::Theta, BrainRegion::Alpha, BrainRegion::Beta, BrainRegion::Gamma};
        for (int j = 0; j < 5; j++) {
            double amp = amp_dist(gen); // Base amplitude for all waves
            if (prominentRegion == regions[j]) {
                amp *= 2.0; // Emphasize the amplitude for the prominent region
            }
            brainWave[i] += amp * std::sin(2.0 * M_PI * frequencies[j] * time + phase_dist(gen));
        }

        // Add Gaussian noise to the signal
        brainWave[i] += noise_dist(gen);
    }

    emit newSignalGenerated(brainWave); // Emit a signal indicating a new brainwave signal has been generated
    return brainWave; // Return the generated brainwave signal
}
