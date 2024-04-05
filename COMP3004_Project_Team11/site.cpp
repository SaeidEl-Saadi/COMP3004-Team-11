#include "site.h"

Site::Site(QObject *parent) : QObject{parent} {
    // start with an empty signal
    currSignal = QVector<double>();
}


void Site::readOriginalSignal(){
    QLineSeries* signal = generateSignal(256, 60);

    for (const QPointF& point : signal->points()) {
        currSignal.push_back(point.y());
    }
}
