#ifndef SITE_H
#define SITE_H

#include <QObject>
#include "treatment.h"
#include "signalgenerator.h"

using namespace SignalGenerator;
using namespace QtCharts;

class Site : public QObject
{
    Q_OBJECT

    private:
        // starts with signal being the baseline and then we keep adding to it
        QVector<double> currSignal;

    public:
        explicit Site(QObject *parent = nullptr);

        //getter
        QVector<double> getSignal() { return currSignal; }

    // internal
    private:
        void readOriginalSignal();
        void applySignal(QVector<double> signal);
};

#endif // SITE_H
