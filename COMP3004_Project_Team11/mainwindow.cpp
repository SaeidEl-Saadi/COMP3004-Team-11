#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "device.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    //instantiate device
    device = new Device(2, this);

    //setup battery timer
    ui->setupUi(this);
    timer = new QTimer(this);
    QObject::connect(timer, &QTimer::timeout, this, &MainWindow::batteryDecrease);
    timer->start(10000);

    //setup green light timer
    greenTimer = new QTimer(this);
    greenTimer->setSingleShot(true);
    QObject::connect(greenTimer, &QTimer::timeout, this, &MainWindow::greenLightBlink);

    //setup red light timer
    redTimer = new QTimer(this);
    QObject::connect(redTimer, &QTimer::timeout, this, &MainWindow::redLightBlink);

    //setup countdown timer
    countDown = new QTimer(this);
    countDown->setSingleShot(true);
    QObject::connect(countDown, &QTimer::timeout, this, &MainWindow::handleCountDown);

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
    connect(ui->setDateTime, &QAbstractButton::released, this, &MainWindow::handleSubmitDateTime);
    connect(ui->reconnect, &QAbstractButton::released, this, &MainWindow::handleReconnectButton);

    //other stuff
    ui->reconnect->hide();

    //setup chart
    QChart *chart = new QChart();
    chart->setTitle("I hate these f***ing charts");
    chart->createDefaultAxes();
    ui->sinewaves->setChart(chart);
    ui->sinewaves->setRenderHint(QPainter::Antialiasing);

}

MainWindow::~MainWindow()
{
    delete ui;
    delete timer;
    delete greenTimer;
    delete redTimer;
    delete device;
    delete countDown;
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

void MainWindow::print(QString str) {
    ui->eventLog->append("> " + str);
    delay();
}

void MainWindow::delay(int time) {
    QTimer timer;
    QEventLoop loop;
    QObject::connect(&timer, &QTimer::timeout, &loop, &QEventLoop::quit);
    timer.start(time);
    loop.exec();
}

void MainWindow::sessionTimerDecrease() {
    if (sessionTime > 10) {
        ui->sessionTimer->setText("0:" + QString::fromStdString(std::to_string(--sessionTime)));
    } else {
        ui->sessionTimer->setText("0:0" + QString::fromStdString(std::to_string(--sessionTime)));
    }
    ui->progressBar->setValue(ui->progressBar->value() + 5);
}

bool MainWindow::sessionChecks() {
    if (stopped || isPowerOff) {
        ui->progressBar->setValue(0);
        ui->sessionTimer->setText("0:00");
        stopped = false;
        ui->eventLog->append("> Session stopping...");
        return true;
    }
    return false;
}

//slots
void MainWindow::handlePowerButton() {
    if (!isPowerOff) {
        isPowerOff = true;
        sessionRunning = false;
        ui->reconnect->hide();
        ui->menu->setDisabled(true);
        ui->offScreen->show();
        ui->play->setDisabled(true);
        ui->pause->setDisabled(true);
        ui->stop->setDisabled(true);
        ui->upload->setDisabled(true);
        turnOffLights();
        ui->progressBar->setValue(0);
        stopped = false;
        paused = false;
        ui->sessionTimer->setText("0:00");
        timer->stop();
        redTimer->stop();
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
    ui->eventLog->append("> Battery Charged");
}

void MainWindow::handleLowBatteryButton() {
    battery = 15;
    batteryDecrease();
    if (!isPowerOff) {
        timer->start(1000);
    }
}

void MainWindow::handleNewSessionButton() {
    // BACK END
    if(!device->startNewSession())
        return; 

    // Sessions from Device class: returns QVector<Session*>
    // Session* sessions = device->getSessions()

    // roundSignals from Session class: returns QVector<QVector<QLineSeries*>>
    // QVector<QVector<QLineSeries*>> roundSignals = session->getRoundSignals();
    // roundSignals structure(always 5 rounds, but variable sites):
        // [round 1] = [site 1 signal, site 2 signal, site 3 signal, site 4 signal, site 5 signal, site 6 signal, site 7 signal] 
        // [round 2] = [site 1 signal, site 2 signal, site 3 signal, site 4 signal, site 5 signal, site 6 signal, site 7 signal]
        // ....
        // [round 5] = [site 1 signal, site 2 signal, site 3 signal, site 4 signal, site 5 signal, site 6 signal, site 7 signal]

    // delete last session
    // device->deleteLastSession();

    // //FRONT END
    // sessionRunning = true;
    // hideMenus();
    // menus[1]->show();
    // ui->menu->setDisabled(true);
    // ui->upload->setDisabled(true);
    // ui->blueLight->setStyleSheet("background-color: rgba(0, 0, 255, 1);");

    // //SESSION STARTS HERE
    // stopped = false;
    // paused = false;
    // print("Average baseline frequences calculated");
    // ui->sessionTimer->setText("0:21");
    // sessionTime = 21;
    // print("Administering treatment...");
    // ui->pause->setDisabled(false);
    // ui->play->setDisabled(false);
    // ui->stop->setDisabled(false);
    // bool check;

    // for (int i = 0; i < 21; i++) {
    //     sessionTimerDecrease();

    //     ui->greenLight->setStyleSheet("background-color: rgba(0, 255, 0, 1);");
    //     greenTimer->start(100);
    //     delay();

    //     check = sessionChecks();
    //     if (check) {
    //         sessionRunning = false;
    //         return;
    //     }
    //     if (paused) {
    //         ui->eventLog->append("> Session paused");
    //         sessionRunning = false;
    //         while (paused) {
    //             delay();
    //             check = sessionChecks();
    //             if (check) return;
    //         }
    //         ui->eventLog->append("> Session resumed");
    //         sessionRunning = true;
    //     }
    // }

    // //SESSION OVER RETURN EVERYTHING BACK
    // ui->stop->click();
    // ui->progressBar->setValue(0);
    
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
    paused = true;
}

void MainWindow::handlePlayButton() {
    paused = false;
}

void MainWindow::handleStopButton() {
    //RESET SESSION HUD TIMER AND PROGRESS BAR
    ui->menu->setDisabled(false);
    stopped = true;
    handleMenuButton();
}

void MainWindow::handleUploadButton() {

}

void MainWindow::handleDisconnectHeadsetButton() {
    if (!sessionRunning) return;
    ui->reconnect->show();
    paused = true;
    ui->eventLog->append("> WARNING: EEG Headset disconnected. Awaiting reconnection.");
    turnOffLights();
    redTimer->start(500);
    countDown->start(10000);
    ui->pause->setDisabled(true);
    ui->play->setDisabled(true);
    ui->stop->setDisabled(true);
}

void MainWindow::handleSubmitDateTime() {
    QDateTime datetime = ui->DateTime->dateTime();
    device->setDateTime(datetime);
}

void MainWindow::handleReconnectButton() {
    ui->reconnect->hide();
    paused = false;
    ui->eventLog->append("> Headset reconnected. Resuming session");
    redTimer->stop();
    ui->pause->setDisabled(false);
    ui->play->setDisabled(false);
    ui->stop->setDisabled(false);
    ui->blueLight->setStyleSheet("background-color: rgba(0, 0, 255, 1);");
    ui->redLight->setStyleSheet("background-color: rgba(255, 0, 0, 0.2);");
}

void MainWindow::handleCountDown() {
    if (isPowerOff) return;
    ui->power->click();
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
        if (batteryMessage == false) {
            ui->eventLog->append("> WARNING: Battery levels low. Please charge the device.");
            batteryMessage = true;
        }
    } else {
        ui->battery->setTextColor("black");
        ui->batteryLabel->setStyleSheet("font: 10pt DejaVu Sans Mono;\ncolor: black;");
        batteryMessage = false;
    }
    ui->battery->clear();
    ui->battery->append(QString::fromStdString(std::to_string(battery) + "%"));
}


void MainWindow::greenLightBlink() {
    ui->greenLight->setStyleSheet("background-color: rgba(0, 255, 0, 0.2);");
    greenTimer->stop();
}

void MainWindow::redLightBlink() {
    if (!redOn) {
        redOn = true;
        ui->redLight->setStyleSheet("background-color: rgba(255, 0, 0, 1);");
    } else {
        ui->redLight->setStyleSheet("background-color: rgba(255, 0, 0, 0.2);");
        redOn = false;
    }
}

// an example of displayChart function
void MainWindow::displayChart(QtCharts::QLineSeries *newSeries) {
    QChart *chart = ui->sinewaves->chart();

    // Remove all series from the chart
    QList<QAbstractSeries *> oldSeries = chart->series();
    for (QAbstractSeries *series : oldSeries) {
        chart->removeSeries(series);
    }

    // Add the new series to the chart
    chart->addSeries(newSeries);
    chart->createDefaultAxes(); // Recreate axes to fit the new series
}


