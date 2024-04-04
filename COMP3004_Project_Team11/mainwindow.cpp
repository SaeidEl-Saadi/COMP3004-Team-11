#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "device.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    //instantiate device
    device = new Device(10, 3, this);

    //setup battery timer
    ui->setupUi(this);
    timer = new QTimer(this);
    QObject::connect(timer, &QTimer::timeout, this, &MainWindow::batteryDecrease);
    timer->start(10000);

    //setup menus
    menus.push_back(ui->mainMenu);
    menus.push_back(ui->sessionMenu);
    menus.push_back(ui->sessionHistoryMenu);
    menus.push_back(ui->setDateTimeMenu);
    hideMenus();
    menus[0]->show();

    //connect buttons
    connect(ui->power, &QAbstractButton::released, this, &MainWindow::handlePowerButton);
    connect(ui->menu, &QAbstractButton::released, this, &MainWindow::handleMenuButton);
    connect(ui->chargeDevice, &QAbstractButton::released, this, &MainWindow::handleChargeDeviceButton);
    connect(ui->lowBattery, &QAbstractButton::released, this, &MainWindow::handleLowBatteryButton);
    connect(ui->newSessionButton, &QAbstractButton::released, this, &MainWindow::handleNewSessionButton);
    connect(ui->viewSessionButton, &QAbstractButton::released, this, &MainWindow::handleSessionHistoryButton);
    connect(ui->setDateTimeButton, &QAbstractButton::released, this, &MainWindow::handleDateTimeButton);
    connect(ui->upload, &QAbstractButton::released, this, &MainWindow::handleUploadButton);
    connect(ui->play, &QAbstractButton::released, this, &MainWindow::handlePlayButton);
    connect(ui->pause, &QAbstractButton::released, this, &MainWindow::handlePauseButton);
    connect(ui->stop, &QAbstractButton::released, this, &MainWindow::handleStopButton);
    connect(ui->dcHeadset, &QAbstractButton::released, this, &MainWindow::handleDisconnectHeadsetButton);

}

MainWindow::~MainWindow()
{
    delete ui;
    delete timer;
}

//functions
void MainWindow::hideMenus() {
    for (int i = 0; i < static_cast<int>(menus.size()); i++) {
        menus[i]->hide();
    }

    ui->offScreen->hide();
}

void MainWindow::turnOffLights() {
    ui->redLight->setStyleSheet("background-color: rgba(255, 0, 0, 0.2);");
    ui->blueLight->setStyleSheet("background-color: rgba(0, 0, 255, 0.2);");
    ui->greenLight->setStyleSheet("background-color: rgba(0, 255, 0, 0.2);");
}

//slots
void MainWindow::handlePowerButton() {
    if (!isPowerOff) {
        isPowerOff = true;
        ui->menu->setDisabled(true);
        ui->offScreen->show();
        ui->play->setDisabled(true);
        ui->pause->setDisabled(true);
        ui->stop->setDisabled(true);
        ui->upload->setDisabled(true);
        turnOffLights();
        timer->stop();
    } else {
        isPowerOff = false;
        ui->menu->setDisabled(false);
        ui->upload->setDisabled(false);
        hideMenus();
        ui->offScreen->hide();
        menus[0]->show();
        ui->battery->show();
        ui->batteryLabel->show();
        timer->start(10000);
    }
}

void MainWindow::handleMenuButton() {
    hideMenus();
    menus[0]->show();
    ui->pause->setDisabled(true);
    ui->play->setDisabled(true);
    ui->stop->setDisabled(true);
    ui->upload->setDisabled(false);
    turnOffLights();
}

void MainWindow::handleChargeDeviceButton() {
    battery = 101;
    batteryDecrease();

    ui->power->setDisabled(false);

    if (!isPowerOff) {
        timer->start(10000);
    }
}

void MainWindow::handleLowBatteryButton() {
    battery = 15;
    batteryDecrease();
    if (!isPowerOff) {
        timer->start(1000);
    }
}

void MainWindow::handleNewSessionButton() {
    hideMenus();
    menus[1]->show();
    ui->menu->setDisabled(true);
    ui->pause->setDisabled(false);
    ui->play->setDisabled(false);
    ui->stop->setDisabled(false);
    ui->upload->setDisabled(true);
    ui->blueLight->setStyleSheet("background-color: rgba(0, 0, 255, 1);");
    //CALL NEW SESSION WITHIN DEVICE
}

void MainWindow::handleSessionHistoryButton() {
    hideMenus();
    menus[2]->show();
}

void MainWindow::handleDateTimeButton() {
    hideMenus();
    menus[3]->show();
}

void MainWindow::handlePauseButton() {

}

void MainWindow::handlePlayButton() {

}

void MainWindow::handleStopButton() {
    //RESET SESSION HUD TIMER AND PROGRESS BAR
    ui->menu->setDisabled(false);
    handleMenuButton();
}

void MainWindow::handleUploadButton() {

}

void MainWindow::handleDisconnectHeadsetButton() {

}


void MainWindow::batteryDecrease() {
    battery--;
    if (battery == 0) {
        timer->stop();
        ui->power->click();
        ui->power->setDisabled(true);
    } else if (battery <= 10) {
        ui->battery->setTextColor("red");
        ui->batteryLabel->setStyleSheet("font: 10pt DejaVu Sans Mono;\ncolor: red;");
    } else {
        ui->battery->setTextColor("black");
        ui->batteryLabel->setStyleSheet("font: 10pt DejaVu Sans Mono;\ncolor: black;");
    }
    ui->battery->clear();
    ui->battery->append(QString::fromStdString(std::to_string(battery) + "%"));
}

