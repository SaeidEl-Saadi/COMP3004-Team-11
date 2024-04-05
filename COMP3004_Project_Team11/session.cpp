#include "session.h"
#include "mainwindow.h"

Session::Session(QDate date, QObject *parent){
    this->date = date;

    // Create 21 empty sites
    for (int i = 0; i < 21; i++){
        sites.push_back(new Site(parent));
    }
}

void Session::setDate(QDate date){
    this->date = date;
}

QDate Session::getDate(){
    return date;
}

void Session::readSignal(){
    for (Site *site : sites){
        site->readOriginalSignal();
    }
}





