#include "site.h"

Site::Site(SignalGenProcess* generator){
    // generator
    this->generator = generator;

    // srand(time(NULL));
    srand(42);

    // frequency bands: alpha [8-12Hz], beta [12-30Hz], delta [1-4Hz], theta [4-8Hz]
    alphaFreq = 8.0 + (rand() / (float)RAND_MAX) * 4.0;
    betaFreq = 12.0 + (rand() / (float)RAND_MAX) * 18.0;
    deltaFreq = 1.0 + (rand() / (float)RAND_MAX) * 3.0;
    thetaFreq = 4.0 + (rand() / (float)RAND_MAX) * 4.0;

    // amplitude bands [0.8, 1.2]
    alphaAmp = 0.8 + (rand() / (float)RAND_MAX) * 0.4;
    betaAmp = 0.8 + (rand() / (float)RAND_MAX) * 0.4;
    deltaAmp = 0.8 + (rand() / (float)RAND_MAX) * 0.4;
    thetaAmp = 0.8 + (rand() / (float)RAND_MAX) * 0.4;
}

void Site::newAmp(){
    alphaAmp = 0.8 + (rand() / (float)RAND_MAX) * 0.4;
    betaAmp = 0.8 + (rand() / (float)RAND_MAX) * 0.4;
    deltaAmp = 0.8 + (rand() / (float)RAND_MAX) * 0.4;
    thetaAmp = 0.8 + (rand() / (float)RAND_MAX) * 0.4;
}

void Site::newFreq(){
    alphaFreq = 8.0 + (rand() / (float)RAND_MAX) * 4.0;
    betaFreq = 12.0 + (rand() / (float)RAND_MAX) * 18.0;
    deltaFreq = 1.0 + (rand() / (float)RAND_MAX) * 3.0;
    thetaFreq = 4.0 + (rand() / (float)RAND_MAX) * 4.0;
}

// we will simulate a signal being read by generating one
void Site::readSignal(){ generateSignal(); }

// generate a signal
void Site::generateSignal(){ 
    currSignal = generator->generate(alphaFreq, alphaAmp, betaFreq, betaAmp, deltaFreq, deltaAmp, thetaFreq, thetaAmp);
}

// get the dominant frequency
double Site::getDominantFrequency(){
    double fd = generator->calculateDominantFrequency(alphaFreq, alphaAmp, betaFreq, betaAmp, deltaFreq, deltaAmp, thetaFreq, thetaAmp);
    return fd;
}