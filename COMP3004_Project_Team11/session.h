#ifndef SESSION_H
#define SESSION_H

#include <QDate>
#include <QObject>

class Session : QObject {
    Q_OBJECT

    private:
        QVector<Site> sites;
        QDate date; // date and time it starts
        QVector<double> avgBefore;
        QVector<double> avgAfter;
        
    public:
        explicit Session(QDate date, QObject *parent = nullptr);
        void setDate(QDate date);
    
    private:
        void readSignal(); // read the signals from the sites
    
    // signals:

    // public slots:

}

#endif