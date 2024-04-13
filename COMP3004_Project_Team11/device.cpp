#include "device.h"
#include "mainwindow.h"

Device::Device(int numSites, MainWindow* ui, QObject *parent) : QObject{parent} {

    // generator for all the sites
    SignalGenProcess* generator = new SignalGenProcess(5.0, 10.0); // 5 seconds, 10 samples per second

    // create all the sites
    for (int i = 0; i < numSites; i++) {
        // generator, double alphaFreq, double betaFreq, double deltaFreq, double thetaFreq, double alphaAmp, double betaAmp, double deltaAmp, double thetaAmp);
        Site* site = new Site(generator, 9.0, 13.0, 2.0, 5.0, 1.0, 1.0, 25.0, 1.0); // for delta waves
        sites.push_back(site);
    }

    // set the number of sites
    this->numSites = numSites;

    // set the main window
    mainWindow = ui;
}

void Device::setDateTime(QDateTime datetime){
    this->datetime = datetime;
    actualTimeSet = QDateTime::currentDateTime();
}

QDateTime Device::getCurrentDateTime(){
    qint64 elapsedTime = actualTimeSet.secsTo(QDateTime::currentDateTime());
    return datetime.addSecs(elapsedTime);
}


// start session 

// read signals calculate baseline before and display graphs

// for 4 rounds(5 sec read + 1 sec treat = 6 sec each round):
//   for each EEG Site:
//     get dominant frequency and amplitude
//     apply treatement
//     read signal
//     update graph

// 4 * 6 = 24 sec + 5 = 29 sec

bool Device::startNewSession(){
    // check if datetime is set
    if (datetime.isNull()){
        printToGUI("Please set the date and time first.");
        return false;
    }

    // create a session
    Session* session = new Session(this->numSites, getCurrentDateTime());

    // generate signal for each site
    for (int i = 0; i < sites.size(); i++){
        sites[i]->readSignal();
    }

    // calculate baseline before treatment
    session->setAvgBefore(getBaseLine());

    // update graphs for this round
    for (int i = 0; i < sites.size(); i++){
        session->setRoundSignal(0, i, sites[i]->getSignal());
    }

    double offset = 5.0;

    for (int i = 0; i < 4; i++) {

        for (int j = 0; j < sites.size(); j++){
            // get dominant frequency
            double fd = sites[i]->getDominantFrequency();
            FreqBand band = getFreqBand(fd);

            // add offset to dominant frequency(apply treatment)
            addOffset(band, offset, sites[j]);

            // generate signal
            sites[j]->readSignal();

            // update graphs for this round
            session->setRoundSignal(i, j, sites[j]->getSignal());
        }

        offset += 5.0;
    }

    // calculate baseline after treatment
    session->setAvgAfter(getBaseLine());

    // add session to the list
    sessions.push_back(session);

    return true;
}

void Device::printToGUI(QString message){
    mainWindow->print(message);
}

double Device::getBaseLine(){
    // check if initial signal is generated
    if (sites[0]->getSignal() == nullptr){
        printToGUI("Please generate the initial signal first.");
        return -1.0;
    }

    double avgBaseline = sites[0]->getDominantFrequency();

    for (int i = 1; i < sites.size(); i++){
        double fd = sites[i]->getDominantFrequency();
    }

    return avgBaseline/sites.size();
}

// alpha [8-12Hz], beta [12-30Hz], delta [1-4Hz], theta [4-8Hz]
FreqBand Device::getFreqBand(double fd){
    if (fd >= 8.0 && fd <= 12.0)
        return FreqBand::ALPHA;
    else if (fd > 12.0 && fd <= 30.0)
        return FreqBand::BETA;
    else if (fd >= 1.0 && fd <= 4.0)
        return FreqBand::DELTA;
    else if (fd > 4.0 && fd <= 8.0)
        return FreqBand::THETA;
    else
        return FreqBand::NONE;
}

void Device::addOffset(FreqBand band, double offset, Site* site) {
    if (band == FreqBand::ALPHA)
        site->addAlphaFreq(offset);
    else if (band == FreqBand::BETA)
        site->addBetaFreq(offset);
    else if (band == FreqBand::DELTA)
        site->addDeltaFreq(offset);
    else if (band == FreqBand::THETA)
        site->addThetaFreq(offset);
}
