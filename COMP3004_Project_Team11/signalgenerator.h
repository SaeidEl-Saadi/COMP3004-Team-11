// SignalGenerator.h

#ifndef SIGNALGENERATOR_H
#define SIGNALGENERATOR_H

#include <QObject>
#include <QtCharts/QLineSeries>

using namespace QtCharts;

class SignalGenerator : public QObject
{
    Q_OBJECT

public:
    explicit SignalGenerator(QObject *parent = nullptr);
    QLineSeries* generateSignal(int sampleRate, int durationSeconds);

private:
    struct FrequencyBand {
        double frequency;
        double amplitude;
    };
};

#endif // SIGNALGENERATOR_H
