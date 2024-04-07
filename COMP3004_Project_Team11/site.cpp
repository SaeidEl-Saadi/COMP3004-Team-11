#include "site.h"

Site::Site(BrainWaveGenerator* generator , QObject *parent) : QObject{parent}, generator(generator) {}

// we will simulate a signal being read by generating one
void Site::readInitialSignal(){ generateSignal(); }

// generate a signal
void Site::generateSignal(){ 
    currSignal = generator->generate();
} 