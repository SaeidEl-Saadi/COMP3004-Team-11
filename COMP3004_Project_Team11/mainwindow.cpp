#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

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

//slots
void MainWindow::handlePowerButton() {
    if (!isPowerOff) {
        isPowerOff = true;
        ui->menu->setDisabled(true);
        ui->offScreen->show();
        ui->play->setDisabled(true);
        ui->pause->setDisabled(true);
        timer->stop();
    } else {
        isPowerOff = false;
        ui->menu->setDisabled(false);
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
}

void MainWindow::handleChargeDeviceButton() {
    battery = 101;
    batteryDecrease();
    timer->start(10000);

    ui->power->setDisabled(false);
}

void MainWindow::handleLowBatteryButton() {
    battery = 15;
    batteryDecrease();
    timer->start(1000);
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

