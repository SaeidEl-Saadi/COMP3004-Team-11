#include "site.h"

Site::Site(SignalGenProcess* generator, double alphaFreq, double betaFreq, double deltaFreq, double thetaFreq, double alphaAmp, double betaAmp, double deltaAmp, double thetaAmp){
    // generator
    this->generator = generator;

    this->currSignal = nullptr;
    
    // frequency bands
    this->alphaFreq = alphaFreq;
    this->betaFreq = betaFreq;
    this->deltaFreq = deltaFreq;
    this->thetaFreq = thetaFreq;

    // amplitude bands
    this->alphaAmp = alphaAmp;
    this->betaAmp = betaAmp;
    this->deltaAmp = deltaAmp;
    this->thetaAmp = thetaAmp;
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