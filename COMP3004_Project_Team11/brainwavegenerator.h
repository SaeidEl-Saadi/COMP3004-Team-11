// BrainWaveGenerator.h

#ifndef BRAINWAVEGENERATOR_H
#define BRAINWAVEGENERATOR_H

#include <QObject>
#include <vector>

class BrainWaveGenerator : public QObject {
    Q_OBJECT

public:
    enum BrainRegion { Delta, Theta, Alpha, Beta, Gamma };
    explicit BrainWaveGenerator(int sampleRate, int duration, BrainRegion region, bool fixedSeed = false, QObject *parent = nullptr);
    std::vector<double> generate();

private:
    int sampleRate;
    int duration;
    bool fixedSeed;
    unsigned int seed;
    BrainRegion prominentRegion;

signals:
    void newSignalGenerated(const std::vector<double>&);
};

#endif // BRAINWAVEGENERATOR_H
