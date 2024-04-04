#include "session.h"
#include "mainwindow.h"


Session::Session(QDate date, QObject *parent){
    this.date = date;
    this.parent = parent;

    // Create 21 empty sites
    for (int i = 0; i < 21; i++){
        sites.push_back(new Site());
    }
}

Session::~Session(){
    for (Site site : sites){
        delete site;
    }
}

void Session::setDate(QDate date){
    this.date = date;
}

void Sesssion::readSignal(){
    for (Site site : sites){
        site.readOriginalSignal();
    }
}





