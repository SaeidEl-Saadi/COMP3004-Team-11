/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDateTimeEdit>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>
#include "QtCharts/QChartView"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QWidget *widget;
    QWidget *mainMenu;
    QPushButton *newSessionButton;
    QPushButton *viewSessionButton;
    QPushButton *setDateTimeButton;
    QPushButton *menu;
    QPushButton *pause;
    QPushButton *play;
    QFrame *blueLight;
    QFrame *greenLight;
    QFrame *redLight;
    QPushButton *power;
    QLabel *batteryLabel;
    QTextEdit *battery;
    QPushButton *stop;
    QPushButton *upload;
    QWidget *sessionMenu;
    QLabel *sessionTimer;
    QProgressBar *progressBar;
    QWidget *sessionHistoryMenu;
    QTextEdit *sessionLogs;
    QWidget *setDateTimeMenu;
    QDateTimeEdit *DateTime;
    QPushButton *setDateTime;
    QWidget *offScreen;
    QPushButton *reconnect;
    QTextEdit *eventLog;
    QLabel *label;
    QLabel *label_2;
    QTextEdit *pc;
    QLabel *label_3;
    QFrame *adminPanel;
    QPushButton *lowBattery;
    QPushButton *dcHeadset;
    QPushButton *chargeDevice;
    QLabel *label_4;
    QChartView *sinewaves;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1310, 800);
        MainWindow->setStyleSheet(QString::fromUtf8("background-color: rgb(218, 218, 218);"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        widget = new QWidget(centralwidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(350, 50, 631, 581));
        widget->setStyleSheet(QString::fromUtf8("background-color: rgb(192, 191, 188);"));
        mainMenu = new QWidget(widget);
        mainMenu->setObjectName(QString::fromUtf8("mainMenu"));
        mainMenu->setGeometry(QRect(180, 170, 251, 241));
        mainMenu->setStyleSheet(QString::fromUtf8("background-color: rgb(246, 245, 244);\n"
""));
        newSessionButton = new QPushButton(mainMenu);
        newSessionButton->setObjectName(QString::fromUtf8("newSessionButton"));
        newSessionButton->setGeometry(QRect(40, 50, 171, 25));
        newSessionButton->setStyleSheet(QString::fromUtf8("font: 10pt \"DejaVu Sans Mono\";\n"
"background-color: rgb(255, 255, 255);"));
        viewSessionButton = new QPushButton(mainMenu);
        viewSessionButton->setObjectName(QString::fromUtf8("viewSessionButton"));
        viewSessionButton->setGeometry(QRect(40, 100, 171, 25));
        viewSessionButton->setStyleSheet(QString::fromUtf8("font: 10pt \"DejaVu Sans Mono\";\n"
"background-color: rgb(255, 255, 255);"));
        setDateTimeButton = new QPushButton(mainMenu);
        setDateTimeButton->setObjectName(QString::fromUtf8("setDateTimeButton"));
        setDateTimeButton->setGeometry(QRect(40, 150, 171, 25));
        setDateTimeButton->setStyleSheet(QString::fromUtf8("font: 10pt \"DejaVu Sans Mono\";\n"
"background-color: rgb(255, 255, 255);"));
        menu = new QPushButton(widget);
        menu->setObjectName(QString::fromUtf8("menu"));
        menu->setEnabled(true);
        menu->setGeometry(QRect(180, 140, 83, 25));
        menu->setAcceptDrops(false);
        menu->setAutoFillBackground(false);
        menu->setStyleSheet(QString::fromUtf8("font: 10pt \"DejaVu Sans Mono\";\n"
"background-color: rgb(255, 255, 255);"));
        menu->setAutoDefault(false);
        menu->setFlat(false);
        pause = new QPushButton(widget);
        pause->setObjectName(QString::fromUtf8("pause"));
        pause->setEnabled(false);
        pause->setGeometry(QRect(180, 420, 83, 25));
        pause->setStyleSheet(QString::fromUtf8("font: 10pt \"DejaVu Sans Mono\";\n"
"background-color: rgb(255, 255, 255);"));
        play = new QPushButton(widget);
        play->setObjectName(QString::fromUtf8("play"));
        play->setEnabled(false);
        play->setGeometry(QRect(270, 420, 83, 25));
        play->setStyleSheet(QString::fromUtf8("font: 10pt \"DejaVu Sans Mono\";\n"
"background-color: rgb(255, 255, 255);"));
        blueLight = new QFrame(widget);
        blueLight->setObjectName(QString::fromUtf8("blueLight"));
        blueLight->setGeometry(QRect(30, 20, 21, 21));
        blueLight->setStyleSheet(QString::fromUtf8("background-color: rgba(0, 0, 255, 0.2);"));
        blueLight->setFrameShape(QFrame::StyledPanel);
        blueLight->setFrameShadow(QFrame::Raised);
        greenLight = new QFrame(widget);
        greenLight->setObjectName(QString::fromUtf8("greenLight"));
        greenLight->setGeometry(QRect(70, 20, 21, 21));
        greenLight->setStyleSheet(QString::fromUtf8("background-color: rgba(0, 255, 0, 0.2);"));
        greenLight->setFrameShape(QFrame::StyledPanel);
        greenLight->setFrameShadow(QFrame::Raised);
        redLight = new QFrame(widget);
        redLight->setObjectName(QString::fromUtf8("redLight"));
        redLight->setGeometry(QRect(110, 20, 21, 21));
        redLight->setStyleSheet(QString::fromUtf8("background-color: rgba(255, 0, 0, 0.2);"));
        redLight->setFrameShape(QFrame::StyledPanel);
        redLight->setFrameShadow(QFrame::Raised);
        power = new QPushButton(widget);
        power->setObjectName(QString::fromUtf8("power"));
        power->setEnabled(true);
        power->setGeometry(QRect(520, 20, 83, 25));
        power->setFocusPolicy(Qt::StrongFocus);
        power->setAcceptDrops(false);
        power->setAutoFillBackground(false);
        power->setStyleSheet(QString::fromUtf8("font: 10pt \"DejaVu Sans Mono\";\n"
"background-color: rgb(255, 255, 255);\n"
""));
        power->setAutoDefault(false);
        power->setFlat(false);
        batteryLabel = new QLabel(widget);
        batteryLabel->setObjectName(QString::fromUtf8("batteryLabel"));
        batteryLabel->setGeometry(QRect(10, 547, 61, 31));
        batteryLabel->setStyleSheet(QString::fromUtf8("font: 10pt \"DejaVu Sans Mono\";"));
        battery = new QTextEdit(widget);
        battery->setObjectName(QString::fromUtf8("battery"));
        battery->setGeometry(QRect(80, 550, 61, 31));
        battery->setStyleSheet(QString::fromUtf8("font: 10pt \"DejaVu Sans Mono\";"));
        battery->setFrameShape(QFrame::NoFrame);
        battery->setFrameShadow(QFrame::Sunken);
        battery->setReadOnly(true);
        stop = new QPushButton(widget);
        stop->setObjectName(QString::fromUtf8("stop"));
        stop->setEnabled(false);
        stop->setGeometry(QRect(180, 450, 83, 25));
        stop->setStyleSheet(QString::fromUtf8("font: 10pt \"DejaVu Sans Mono\";\n"
"background-color: rgb(255, 255, 255);"));
        upload = new QPushButton(widget);
        upload->setObjectName(QString::fromUtf8("upload"));
        upload->setEnabled(true);
        upload->setGeometry(QRect(520, 540, 83, 25));
        upload->setStyleSheet(QString::fromUtf8("font: 10pt \"DejaVu Sans Mono\";\n"
"background-color: rgb(255, 255, 255);"));
        sessionMenu = new QWidget(widget);
        sessionMenu->setObjectName(QString::fromUtf8("sessionMenu"));
        sessionMenu->setGeometry(QRect(180, 170, 251, 241));
        sessionMenu->setStyleSheet(QString::fromUtf8("background-color: rgb(246, 245, 244);\n"
""));
        sessionTimer = new QLabel(sessionMenu);
        sessionTimer->setObjectName(QString::fromUtf8("sessionTimer"));
        sessionTimer->setGeometry(QRect(80, 50, 101, 51));
        sessionTimer->setStyleSheet(QString::fromUtf8("font: 30pt \"DejaVu Sans Mono\";"));
        progressBar = new QProgressBar(sessionMenu);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setGeometry(QRect(60, 140, 141, 23));
        QFont font;
        font.setFamily(QString::fromUtf8("DejaVu Sans Mono"));
        progressBar->setFont(font);
        progressBar->setValue(0);
        sessionHistoryMenu = new QWidget(widget);
        sessionHistoryMenu->setObjectName(QString::fromUtf8("sessionHistoryMenu"));
        sessionHistoryMenu->setGeometry(QRect(180, 170, 251, 241));
        sessionHistoryMenu->setStyleSheet(QString::fromUtf8("background-color: rgb(246, 245, 244);\n"
""));
        sessionLogs = new QTextEdit(sessionHistoryMenu);
        sessionLogs->setObjectName(QString::fromUtf8("sessionLogs"));
        sessionLogs->setGeometry(QRect(20, 20, 211, 201));
        sessionLogs->setStyleSheet(QString::fromUtf8("font: 10pt \"DejaVu Sans Mono\";"));
        sessionLogs->setFrameShape(QFrame::Box);
        sessionLogs->setFrameShadow(QFrame::Plain);
        sessionLogs->setReadOnly(true);
        setDateTimeMenu = new QWidget(widget);
        setDateTimeMenu->setObjectName(QString::fromUtf8("setDateTimeMenu"));
        setDateTimeMenu->setGeometry(QRect(180, 170, 251, 241));
        setDateTimeMenu->setStyleSheet(QString::fromUtf8("background-color: rgb(246, 245, 244);\n"
""));
        DateTime = new QDateTimeEdit(setDateTimeMenu);
        DateTime->setObjectName(QString::fromUtf8("DateTime"));
        DateTime->setGeometry(QRect(30, 50, 194, 26));
        DateTime->setStyleSheet(QString::fromUtf8("font: 10pt \"DejaVu Sans Mono\";"));
        setDateTime = new QPushButton(setDateTimeMenu);
        setDateTime->setObjectName(QString::fromUtf8("setDateTime"));
        setDateTime->setGeometry(QRect(80, 120, 83, 25));
        setDateTime->setStyleSheet(QString::fromUtf8("font: 10pt \"DejaVu Sans Mono\";\n"
"background-color: rgb(255, 255, 255);"));
        offScreen = new QWidget(widget);
        offScreen->setObjectName(QString::fromUtf8("offScreen"));
        offScreen->setGeometry(QRect(180, 170, 251, 241));
        offScreen->setStyleSheet(QString::fromUtf8("background-color: rgb(246, 245, 244);\n"
""));
        reconnect = new QPushButton(widget);
        reconnect->setObjectName(QString::fromUtf8("reconnect"));
        reconnect->setGeometry(QRect(250, 520, 111, 51));
        reconnect->setStyleSheet(QString::fromUtf8("font: 10pt \"DejaVu Sans Mono\";\n"
"background-color: rgb(255, 255, 255);"));
        eventLog = new QTextEdit(centralwidget);
        eventLog->setObjectName(QString::fromUtf8("eventLog"));
        eventLog->setGeometry(QRect(1000, 50, 291, 431));
        eventLog->setStyleSheet(QString::fromUtf8("font: 12pt \"DejaVu Sans Mono\";"));
        eventLog->setFrameShape(QFrame::Box);
        eventLog->setFrameShadow(QFrame::Plain);
        eventLog->setLineWidth(1);
        eventLog->setReadOnly(true);
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(1000, 10, 291, 31));
        label->setStyleSheet(QString::fromUtf8("font: 20pt \"DejaVu Sans Mono\";\n"
"color: rgb(0, 0, 0);"));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(360, 0, 481, 41));
        label_2->setStyleSheet(QString::fromUtf8("font: 20pt \"DejaVu Sans Mono\";"));
        pc = new QTextEdit(centralwidget);
        pc->setObjectName(QString::fromUtf8("pc"));
        pc->setGeometry(QRect(10, 50, 321, 441));
        pc->setStyleSheet(QString::fromUtf8("font: 12pt \"DejaVu Sans Mono\";"));
        pc->setFrameShape(QFrame::Box);
        pc->setFrameShadow(QFrame::Plain);
        pc->setLineWidth(1);
        pc->setReadOnly(true);
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(10, 10, 291, 31));
        label_3->setStyleSheet(QString::fromUtf8("font: 20pt \"DejaVu Sans Mono\";\n"
"color: rgb(0, 0, 0);"));
        adminPanel = new QFrame(centralwidget);
        adminPanel->setObjectName(QString::fromUtf8("adminPanel"));
        adminPanel->setGeometry(QRect(10, 580, 321, 161));
        adminPanel->setFrameShape(QFrame::Box);
        adminPanel->setFrameShadow(QFrame::Plain);
        adminPanel->setLineWidth(1);
        lowBattery = new QPushButton(adminPanel);
        lowBattery->setObjectName(QString::fromUtf8("lowBattery"));
        lowBattery->setGeometry(QRect(30, 30, 111, 51));
        lowBattery->setStyleSheet(QString::fromUtf8("font: 10pt \"DejaVu Sans Mono\";\n"
"background-color: rgb(255, 255, 255);"));
        dcHeadset = new QPushButton(adminPanel);
        dcHeadset->setObjectName(QString::fromUtf8("dcHeadset"));
        dcHeadset->setGeometry(QRect(180, 30, 111, 51));
        dcHeadset->setStyleSheet(QString::fromUtf8("font: 10pt \"DejaVu Sans Mono\";\n"
"background-color: rgb(255, 255, 255);"));
        chargeDevice = new QPushButton(adminPanel);
        chargeDevice->setObjectName(QString::fromUtf8("chargeDevice"));
        chargeDevice->setGeometry(QRect(110, 90, 111, 51));
        chargeDevice->setStyleSheet(QString::fromUtf8("font: 10pt \"DejaVu Sans Mono\";\n"
"background-color: rgb(255, 255, 255);"));
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(10, 530, 291, 31));
        label_4->setStyleSheet(QString::fromUtf8("font: 20pt \"DejaVu Sans Mono\";\n"
"color: rgb(0, 0, 0);"));
        sinewaves = new QChartView(centralwidget);
        sinewaves->setObjectName(QString::fromUtf8("sinewaves"));
        sinewaves->setGeometry(QRect(990, 500, 321, 201));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1310, 22));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        menu->setDefault(false);
        power->setDefault(false);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        newSessionButton->setText(QCoreApplication::translate("MainWindow", "Start New Session", nullptr));
        viewSessionButton->setText(QCoreApplication::translate("MainWindow", "View Session History", nullptr));
        setDateTimeButton->setText(QCoreApplication::translate("MainWindow", "Set Date and Time", nullptr));
        menu->setText(QCoreApplication::translate("MainWindow", "Menu", nullptr));
        pause->setText(QCoreApplication::translate("MainWindow", "Pause", nullptr));
        play->setText(QCoreApplication::translate("MainWindow", "Play", nullptr));
        power->setText(QCoreApplication::translate("MainWindow", "Power", nullptr));
        batteryLabel->setText(QCoreApplication::translate("MainWindow", "Battery: ", nullptr));
        battery->setHtml(QCoreApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'DejaVu Sans Mono'; font-size:10pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">100%</p></body></html>", nullptr));
        stop->setText(QCoreApplication::translate("MainWindow", "Stop", nullptr));
        upload->setText(QCoreApplication::translate("MainWindow", "Upload", nullptr));
        sessionTimer->setText(QCoreApplication::translate("MainWindow", "0:00", nullptr));
        setDateTime->setText(QCoreApplication::translate("MainWindow", "Set", nullptr));
        reconnect->setText(QCoreApplication::translate("MainWindow", "Reconnect and\n"
"Continue", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Event Log", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Reset Neurofeedback", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "PC", nullptr));
        lowBattery->setText(QCoreApplication::translate("MainWindow", "Low Battery", nullptr));
        dcHeadset->setText(QCoreApplication::translate("MainWindow", "Disconnect\n"
"Headset", nullptr));
        chargeDevice->setText(QCoreApplication::translate("MainWindow", "Charge Device", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "Admin Panel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
