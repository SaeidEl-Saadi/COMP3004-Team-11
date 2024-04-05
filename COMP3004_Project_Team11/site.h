#ifndef SITE_H
#define SITE_H

#include <QObject>
#include "treatment.h"
#include <vector>

//using namespace SignalGenerator;
//using namespace QtCharts;

class Site : public QObject
{
    Q_OBJECT

    private:
        // starts with signal being the baseline and then we keep adding to it
        std::vector<double> currSignal;

    public:
        Site(QObject *parent = nullptr);
        void readOriginalSignal();

        // setter
        void setSignal(std::vector<double> signal) { currSignal = signal; }

        //getter
        std::vector<double> getSignal() { return currSignal; }

    // internal
    private:
        void applySignal(std::vector<double> signal);
};

#endif // SITE_H
