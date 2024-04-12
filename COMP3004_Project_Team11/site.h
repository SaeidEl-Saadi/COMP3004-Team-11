#ifndef SITE_H
#define SITE_H

#include <QObject>
#include <QDebug>
#include <vector>
#include "sinewavegenerator.h"

class Site : public QObject
{
    Q_OBJECT

    // attributes
    private:
        SineWaveGenerator* generator;
        double frequency;
        std::vector<double> currSignal;

    // methods
    public:
        Site(SineWaveGenerator* generator, double frequency, QObject *parent = nullptr);

        // getters and setters
        void setSignal(std::vector<double> signal) { currSignal = signal; }
        std::vector<double> getSignal() { return currSignal; }
        
        void readInitialSignal(); 

    private:
        void generateSignal();

};

#endif // SITE_H
