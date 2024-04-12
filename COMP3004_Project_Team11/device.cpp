#include "device.h"
#include "mainwindow.h"

Device::Device(int sampleRate, int duration, MainWindow* ui, QObject *parent) : QObject{parent} {


    this->processSignal = new ProcessSignal();

    // generator for all the sites
    SineWaveGenerator* generator = new SineWaveGenerator(sampleRate, duration);

    // create all the sites
    for (int i = 0; i < 21; i++) {
        Site* site = new Site(generator, 5); // frequency is 5
        sites.push_back(site);
    }

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

bool Device::startNewSession(){
    // check if datetime is set
    if (datetime.isNull()){
        printToGUI("Please set the date and time first.");
        return false;
    }

    std::vector<std::vector<double>> allBaselineSignalsTemp;

    // loop through all the sites and read the initial signal
    for (int i = 0; i < sites.size(); i++){
        sites[i]->readInitialSignal(); // this will generate a signal for each site
        allBaselineSignalsTemp.push_back(sites[i]->getSignal());    
    }

    // create a new session
    Session* session = new Session(getCurrentDateTime());

    return true;
}

void Device::printToGUI(QString message){
    mainWindow->print(message);
}