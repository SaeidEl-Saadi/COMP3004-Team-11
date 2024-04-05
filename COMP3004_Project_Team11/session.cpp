#include "session.h"
#include "mainwindow.h"

Session::Session(QDate date, QObject *parent) : QObject(parent), date(date) {

    // Create 21 empty sites
    for (int i = 0; i < 21; i++){
        sites.push_back(new Site(parent));
    }

    // Create a generator
    generator = new BrainWaveGenerator(256, 60, BrainWaveGenerator::Delta);
}


void Session::setDate(QDate date)
{
    this->date = date;
}

QDate Session::getDate(){
    return date;
}

QVector<Site*> Session::getSites(){
    return sites;
}
void Session::readSignal(){
    for (Site *site : sites){
        site->readOriginalSignal();
    }
}

void Session::generateInitialSignals(){
    for(Site *site: sites){
        std::vector<double> signal = generator->generate();
        site->setSignal(signal);
        
    }

    for(Site *site: sites){
        std::vector<double> signal = site->getSignal();
        for (int i = 0; i < signal.size(); i++){
            std::cout << signal[i];
        }
    }

}


