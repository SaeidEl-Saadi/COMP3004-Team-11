#include "device.h"
#include "mainwindow.h"

Device::Device(int numSites, MainWindow* ui, QObject *parent) : QObject{parent} {

    // generator for all the sites
    SignalGenProcess* generator = new SignalGenProcess(5, 10); // 5 seconds, 10 samples per second

    // create all the sites
    for (int i = 0; i < numSites; i++) {
        Site* site = new Site(generator); 
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

     
    // generate signal for each site and set round 1 signal
    for (int i = 0; i < sites.size(); i++){
        sites[i]->readSignal(); // ------------------------------------------------------------------------------------------------------------> ROUND 1 SIGNAL GENERATION
        session->setRoundSignal(0, i, sites[i]->getSignal()); 
    }

    // calculate baseline before treatment
    session->setAvgBefore(getBaseLine()); // --------------------------------------------------------------------------------------------------> BASELINE BEFORE 

    double offset = 5.0;

    for (int i = 1; i < 5; i++) {

        qDebug() << "====Round " << (i) << "====";

        for (int j = 0; j < sites.size(); j++){

            qDebug() << "Site " << (j + 1) << " | Alpha Freq: " << sites[j]->getAlphaFreq() << " | Alpha Amp: " << sites[j]->getAlphaAmp();
            qDebug() << "Site " << (j + 1) << " | Beta Freq : " << sites[j]->getBetaFreq() << " | Beta Amp: " << sites[j]->getBetaAmp();
            qDebug() << "Site " << (j + 1) << " | Delta Freq: " << sites[j]->getDeltaFreq() << " | Delta Amp: " << sites[j]->getDeltaAmp();
            qDebug() << "Site " << (j + 1) << " | Theta Freq: " << sites[j]->getThetaFreq() << " | Theta Amp: " << sites[j]->getThetaAmp();

            // get dominant frequency
            double fd = sites[j]->getDominantFrequency();
            FreqBand band = getFreqBand(fd);

            qDebug() << "Site " << (j + 1) << " | Dominant Freq Band: " << getFreqBandString(band) << " " << fd << "Hz";
            qDebug() << "Site " << (j + 1) << " | Adding offset: " << offset << "Hz to " << getFreqBandString(band);

            // add offset to dominant frequency(apply treatment)
            // addOffset(band, offset, sites[j]); // -----------------------------------------------------------------------------------------------> TREATMENT ADDING OFFSET

            // get new amplitude and signal
            sites[j]->newAmp();
            sites[j]->newFreq();
            sites[j]->readSignal(); // -----------------------------------------------------------------------------------------------------------> ROUND 2-5 SIGNAL GENERATION

            // update graphs for this round
            session->setRoundSignal(i, j, sites[j]->getSignal());
        }

        offset += 5.0; 
    }
    
    
    qDebug() << "====Round 5(last)====";
    qDebug() << "Site 1 | Alpha Freq: " << sites[0]->getAlphaFreq() << " | Alpha Amp: " << sites[0]->getAlphaAmp();
    qDebug() << "Site 1 | Beta Freq : " << sites[0]->getBetaFreq() << " | Beta Amp: " << sites[0]->getBetaAmp();
    qDebug() << "Site 1 | Delta Freq: " << sites[0]->getDeltaFreq() << " | Delta Amp: " << sites[0]->getDeltaAmp();
    qDebug() << "Site 1 | Theta Freq: " << sites[0]->getThetaFreq() << " | Theta Amp: " << sites[0]->getThetaAmp();

    double fd = sites[0]->getDominantFrequency();
    FreqBand band = getFreqBand(fd);
    
    qDebug() << "Site 1 Dominant Freq Band at End: " << getFreqBandString(band) << " " << fd << "Hz";

    // calculate baseline after treatment
    session->setAvgAfter(getBaseLine()); // ------------------------------------------------------------------------------------------------------> BASELINE AFTER 

    // add session to the list
    sessions.push_back(session);

    // reset frequencies
    for(int i = 0;i < sites.size(); i++)
        sites[i]->newFreq();
    
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

QString Device::getFreqBandString(FreqBand band){
    if (band == FreqBand::ALPHA)
        return "Alpha";
    else if (band == FreqBand::BETA)
        return "Beta";
    else if (band == FreqBand::DELTA)
        return "Delta";
    else if (band == FreqBand::THETA)
        return "Theta";
}

void Device::deleteLatestSession(){
    if (sessions.size() == 0){
        return;
    }

    Session* session = sessions[sessions.size() - 1];
    sessions.pop_back();
    delete session;
}
