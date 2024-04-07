#include "device.h"

Device::Device(int sampleRate, int duration, QObject *parent) : QObject{parent} {

    // set the sample rate(just in case to have it)
    this->sampleRate = sampleRate;

    // set the duration(just in case to have it)
    this->duration = duration;

    this->processSignal = new ProcessSignal();

    // create the generators for all wave types
    BrainWaveGenerator* generatorDelta = new BrainWaveGenerator(sampleRate, duration, BrainRegion::Delta);
    BrainWaveGenerator* generatorAlpha = new BrainWaveGenerator(sampleRate, duration, BrainRegion::Alpha);
    BrainWaveGenerator* generatorTheta = new BrainWaveGenerator(sampleRate, duration, BrainRegion::Theta);
    BrainWaveGenerator* generatorGamma = new BrainWaveGenerator(sampleRate, duration, BrainRegion::Gamma);
    BrainWaveGenerator* generatorBeta = new BrainWaveGenerator(sampleRate, duration, BrainRegion::Beta);
    
    // create all the sites
    for (int i = 0; i < 21; i++) {
        Site* site = new Site(generatorBeta);
        sites.push_back(site);
    }
}

QDateTime Device::getCurrentDateTime(){
    qint64 elapsedTime = actualTimeSet.secsTo(QDateTime::currentDateTime());
    return datetime.addSecs(elapsedTime);
}

void Device::startNewSession(){
    
    std::vector<std::vector<double>> allBaselineSignalsTemp;

    // loop through all the sites and read the initial signal
    for (int i = 0; i < sites.size(); i++){
        sites[i]->readInitialSignal(); // this will generate a signal for each site
        allBaselineSignalsTemp.push_back(sites[i]->getSignal());    
    }

    // get total avg baseline
    BrainWaveGenerator* generatorBeta = new BrainWaveGenerator(sampleRate, duration, BrainRegion::Beta);

    std::vector<double> betaWave = generatorBeta->generate();
    std::vector<double> avgBefore = processSignal->calculateBaseline(allBaselineSignalsTemp);
    std::vector<std::complex<double>> FFTSignal = processSignal->performFFT(betaWave);
    double powerSpectrum = processSignal->calculateAverageFrequencyUsingPSD(FFTSignal,sampleRate);
    qDebug() << "size of avgBefore: " << betaWave.size(); 
    qDebug() << "avgBefore: " << betaWave;
    processSignal->printFFT(FFTSignal,sampleRate);
    // qDebug() << "FFT: " << FFTSignal;
    qDebug() << "powerSpectrum " << powerSpectrum;
    // qDebug() << "The Set Date: " << datetime;
    // qDebug() << "The Current Date for the Session: " << getCurrentDateTime();
}