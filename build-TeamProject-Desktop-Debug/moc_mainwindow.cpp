/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../COMP3004_Project_Team11/mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[16];
    char stringdata0[304];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 15), // "batteryDecrease"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 17), // "handlePowerButton"
QT_MOC_LITERAL(4, 46, 16), // "handleMenuButton"
QT_MOC_LITERAL(5, 63, 24), // "handleChargeDeviceButton"
QT_MOC_LITERAL(6, 88, 22), // "handleLowBatteryButton"
QT_MOC_LITERAL(7, 111, 22), // "handleNewSessionButton"
QT_MOC_LITERAL(8, 134, 26), // "handleSessionHistoryButton"
QT_MOC_LITERAL(9, 161, 20), // "handleDateTimeButton"
QT_MOC_LITERAL(10, 182, 17), // "handlePauseButton"
QT_MOC_LITERAL(11, 200, 16), // "handlePlayButton"
QT_MOC_LITERAL(12, 217, 16), // "handleStopButton"
QT_MOC_LITERAL(13, 234, 18), // "handleUploadButton"
QT_MOC_LITERAL(14, 253, 29), // "handleDisconnectHeadsetButton"
QT_MOC_LITERAL(15, 283, 20) // "handleSubmitDateTime"

    },
    "MainWindow\0batteryDecrease\0\0"
    "handlePowerButton\0handleMenuButton\0"
    "handleChargeDeviceButton\0"
    "handleLowBatteryButton\0handleNewSessionButton\0"
    "handleSessionHistoryButton\0"
    "handleDateTimeButton\0handlePauseButton\0"
    "handlePlayButton\0handleStopButton\0"
    "handleUploadButton\0handleDisconnectHeadsetButton\0"
    "handleSubmitDateTime"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   84,    2, 0x08 /* Private */,
       3,    0,   85,    2, 0x08 /* Private */,
       4,    0,   86,    2, 0x08 /* Private */,
       5,    0,   87,    2, 0x08 /* Private */,
       6,    0,   88,    2, 0x08 /* Private */,
       7,    0,   89,    2, 0x08 /* Private */,
       8,    0,   90,    2, 0x08 /* Private */,
       9,    0,   91,    2, 0x08 /* Private */,
      10,    0,   92,    2, 0x08 /* Private */,
      11,    0,   93,    2, 0x08 /* Private */,
      12,    0,   94,    2, 0x08 /* Private */,
      13,    0,   95,    2, 0x08 /* Private */,
      14,    0,   96,    2, 0x08 /* Private */,
      15,    0,   97,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->batteryDecrease(); break;
        case 1: _t->handlePowerButton(); break;
        case 2: _t->handleMenuButton(); break;
        case 3: _t->handleChargeDeviceButton(); break;
        case 4: _t->handleLowBatteryButton(); break;
        case 5: _t->handleNewSessionButton(); break;
        case 6: _t->handleSessionHistoryButton(); break;
        case 7: _t->handleDateTimeButton(); break;
        case 8: _t->handlePauseButton(); break;
        case 9: _t->handlePlayButton(); break;
        case 10: _t->handleStopButton(); break;
        case 11: _t->handleUploadButton(); break;
        case 12: _t->handleDisconnectHeadsetButton(); break;
        case 13: _t->handleSubmitDateTime(); break;
        default: ;
        }
    }
    (void)_a;
}

QT_INIT_METAOBJECT const QMetaObject MainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_MainWindow.data,
    qt_meta_data_MainWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 14;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
