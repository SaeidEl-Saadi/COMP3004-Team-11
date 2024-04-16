#include "device.h"
#include "mainwindow.h"

Device::Device(int numSites, MainWindow* ui, QObject *parent) : QObject{parent} {

    // generator for all the sites
    generatorProcessor = new SignalGenProcess(5, 10); // 5 seconds, 10 samples per second

    // create all the sites
    for (int i = 0; i < numSites; i++) {
        Site* site = new Site(generatorProcessor); 
        sites.push_back(site);
    }

    // set the number of sites
    this->numSites = numSites;

    // set the main window
    mainWindow = ui;
}

Device::~Device(){
    for (int i = 0; i < sites.size(); i++){
        delete sites[i];
    }

    for (int i = 0; i < sessions.size(); i++){
        delete sessions[i];
    }

    delete generatorProcessor;
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

    qDebug() << "Session start at: " << session->getDateTime().toString();

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
            qDebug() << "Site " << (j + 1) << " | Treatment Freq Round 1: " << sites[j]->getTreatFreqRound1() << " | Treatment Ampl Round 1: " << sites[j]->getTreatAmplRound1();
            qDebug() << "Site " << (j + 1) << " | Treatment Freq Round 2: " << sites[j]->getTreatFreqRound2() << " | Treatment Ampl Round 2: " << sites[j]->getTreatAmplRound2();
            qDebug() << "Site " << (j + 1) << " | Treatment Freq Round 3: " << sites[j]->getTreatFreqRound3() << " | Treatment Ampl Round 3: " << sites[j]->getTreatAmplRound3();
            qDebug() << "Site " << (j + 1) << " | Treatment Freq Round 4: " << sites[j]->getTreatFreqRound4() << " | Treatment Ampl Round 4: " << sites[j]->getTreatAmplRound4();
            qDebug() << "Site " << (j + 1) << " | Dominant Freq Band: " << sites[j]->getDominantFrequency() << "Hz";


            // get dominant frequency
            double fd = sites[j]->getDominantFrequency();

            qDebug() << "Site " << (j + 1) << " | Adding offset: " << offset << "Hz to " << fd << "Hz";
            qDebug() << "----------------------";

            sites[j]->setTreatmentFreq(i - 1, fd + offset); // ------------------------------------------------------------------------------------------------------> TREATMENT
            sites[j]->genTreatmentAmpl(i - 1); // -----------------------------------------------------------------------------------------------------------> TREATMENT 

            sites[j]->readSignal(); // -----------------------------------------------------------------------------------------------------------> ROUND 2-5 SIGNAL GENERATION

            // update graphs for this round
            session->setRoundSignal(i, j, sites[j]->getSignal());
        }

        offset += 5.0; 
    }
    qDebug() << "====Round 5====";
    for (int i = 0; i < sites.size(); i++){
        qDebug() << "Site " << (i + 1) << " | Alpha Freq: " << sites[i]->getAlphaFreq() << " | Alpha Amp: " << sites[i]->getAlphaAmp();
        qDebug() << "Site " << (i + 1) << " | Beta Freq : " << sites[i]->getBetaFreq() << " | Beta Amp: " << sites[i]->getBetaAmp();
        qDebug() << "Site " << (i + 1) << " | Delta Freq: " << sites[i]->getDeltaFreq() << " | Delta Amp: " << sites[i]->getDeltaAmp();
        qDebug() << "Site " << (i + 1) << " | Theta Freq: " << sites[i]->getThetaFreq() << " | Theta Amp: " << sites[i]->getThetaAmp();
        qDebug() << "Site " << (i + 1) << " | Treatment Freq Round 1: " << sites[i]->getTreatFreqRound1() << " | Treatment Ampl Round 1: " << sites[i]->getTreatAmplRound1();
        qDebug() << "Site " << (i + 1) << " | Treatment Freq Round 2: " << sites[i]->getTreatFreqRound2() << " | Treatment Ampl Round 2: " << sites[i]->getTreatAmplRound2();
        qDebug() << "Site " << (i + 1) << " | Treatment Freq Round 3: " << sites[i]->getTreatFreqRound3() << " | Treatment Ampl Round 3: " << sites[i]->getTreatAmplRound3();
        qDebug() << "Site " << (i + 1) << " | Treatment Freq Round 4: " << sites[i]->getTreatFreqRound4() << " | Treatment Ampl Round 4: " << sites[i]->getTreatAmplRound4();

        double fd = sites[i]->getDominantFrequency();
        
        qDebug() << "Site " << (i + 1) << " | Dominant Freq at End: " << fd << "Hz";
        qDebug() << "----------------------";

    }

    // calculate baseline after treatment
    session->setAvgAfter(getBaseLine()); // ------------------------------------------------------------------------------------------------------> BASELINE AFTER 
    qDebug() << "====Baseline====";
    qDebug() << "Baseline Before: " << session->getAvgBefore() << "Hz" << " | Baseline After: " << session->getAvgAfter() << "Hz";

    // add session to the list
    sessions.push_back(session);

    // reset sites
    resetSites();
    
    return true;
}

void Device::printToGUI(QString message){
    mainWindow->print(message);
}

double Device::getBaseLine(){
    // check if initial signal is generated
    if (sites[0]->getSignal() == nullptr){
        return -1.0;
    }

    double avgBaseline = sites[0]->getDominantFrequency();

    for (int i = 1; i < sites.size(); i++){
        double fd = sites[i]->getDominantFrequency();
    }

    return avgBaseline/sites.size();
}

void Device::deleteLatestSession(){
    if (sessions.size() == 0){
        return;
    }

    Session* session = sessions[sessions.size() - 1];
    sessions.pop_back();
    delete session;
}

void Device::resetSites(){
    for (int i = 0; i < sites.size(); i++){
        sites[i]->resetSite();
    }
}
