#ifndef SITE_H
#define SITE_H

#include <QObject>
#include <QDebug>
#include <vector>
#include "brainwavegenerator.h"

class Site : public QObject
{
    Q_OBJECT

    // attributes
    private:
        BrainWaveGenerator* generator;
        std::vector<double> currSignal;

    // methods
    public:
        Site(BrainWaveGenerator* generator , QObject *parent = nullptr);

        // getters and setters
        void setSignal(std::vector<double> signal) { currSignal = signal; }
        std::vector<double> getSignal() { return currSignal; }
        
        void readInitialSignal(); 

    private:
        void generateSignal();

};

#endif // SITE_H
