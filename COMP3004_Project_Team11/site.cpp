#include "site.h"

Site::Site(SineWaveGenerator* generator, double frequency, QObject *parent) : QObject{parent} {
    this->generator = generator;
    this->frequency = frequency;
}

// we will simulate a signal being read by generating one
void Site::readInitialSignal(){ generateSignal(); }

// generate a signal
void Site::generateSignal(){ 
    currSignal = generator->generate(this->frequency);
}