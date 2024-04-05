#include "processsignal.h"

// Constructor for the ProcessSignal class, initializes the QObject with the provided parent
ProcessSignal::ProcessSignal(QObject *parent)
    : QObject{parent} {
    // Constructor body is empty as there's no specific initialization required here
}

// Calculates the baseline (average) of multiple signals
std::vector<double> ProcessSignal::calculateBaseline(const std::vector<std::vector<double>>& sigs) {
    if (sigs.empty()) {
        throw std::invalid_argument("The list of signals is empty.");
        // If the input vector of signals is empty, throw an exception
    }

    size_t numSamples = sigs.front().size(); // Number of samples in the first signal
    for (const auto& signal : sigs) {
        if (signal.size() != numSamples) {
            throw std::invalid_argument("Not all signals have the same length.");
            // Each signal should have the same number of samples, throw an exception if not
        }
    }

    std::vector<double> baseline(numSamples, 0.0); // Initialize the baseline signal with zeros

    for (size_t i = 0; i < numSamples; ++i) {
        // Sum up the i-th sample from each signal
        double sum = std::accumulate(sigs.begin(), sigs.end(), 0.0,
                                     [i](double acc, const std::vector<double>& signal) {
                                         return acc + signal[i];
                                     });
        baseline[i] = sum / sigs.size(); // Calculate the average for the i-th sample
    }

    return baseline; // Return the computed baseline signal
}

// Applies the Fast Fourier Transform (FFT) to a signal
void ProcessSignal::applyFFT(std::vector<std::complex<double>>& data) {
    const double PI = 3.141592653589793238460; // Define PI for calculation
    size_t N = data.size(); // Size of the input data
    if (N <= 1) return; // Base case for recursion: if the dataset is a single element or empty

    // Divide the data into even and odd indexed elements
    std::vector<std::complex<double>> even(N / 2), odd(N / 2);
    for (size_t i = 0; i < N / 2; ++i) {
        even[i] = data[i * 2];
        odd[i] = data[i * 2 + 1];
    }

    // Recursive calls for even and odd parts
    applyFFT(even);
    applyFFT(odd);

    // Combine the results of the FFT from the even and odd parts
    for (size_t k = 0; k < N / 2; ++k) {
        std::complex<double> t = std::polar(1.0, -2 * PI * k / N) * odd[k];
        data[k] = even[k] + t;
        data[k + N / 2] = even[k] - t;
    }
}

// Converts a real-valued signal to complex and performs FFT on it
std::vector<std::complex<double>> ProcessSignal::performFFT(const std::vector<double>& realSignal) {
    std::vector<std::complex<double>> FFTSignal(realSignal.size());

    // Convert each real sample to a complex number with zero imaginary part
    for(size_t i = 0; i < realSignal.size(); ++i) {
        FFTSignal[i] = std::complex<double>(realSignal[i], 0.0);
    }

    // Apply FFT to the complex representation of the signal
    applyFFT(FFTSignal);

    return FFTSignal; // Return the FFT-transformed signal
}

// Calculates the power-weighted average frequency of a signal given its FFT result
double ProcessSignal::calculateAverageFrequencyUsingPSD(const std::vector<std::complex<double>>& fftResult, double sampleRate) {
    double totalPower = 0.0; // Total power in the signal
    double weightedFrequencySum = 0.0; // Sum of frequencies weighted by their power

    size_t N = fftResult.size(); // Number of points in the FFT result
    // Iterate only over the first half due to symmetry in FFT of real-valued signals
    for (size_t i = 0; i < N / 2; ++i) {
        double power = std::norm(fftResult[i]); // Power of the i-th frequency bin (magnitude squared)
        totalPower += power;
        // Frequency for this bin: (i * sampleRate / N), weighted by its power
        weightedFrequencySum += power * (i * sampleRate / N);
    }

    if (totalPower == 0) return 0; // Avoid division by zero
    return weightedFrequencySum / totalPower; // Return the average frequency weighted by power
}
