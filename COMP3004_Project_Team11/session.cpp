#include "session.h"

Session::Session(QDateTime datetime, QObject *parent) : QObject(parent), datetime(datetime) {}