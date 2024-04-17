#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "device.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    //instantiate device
    device = new Device(7, this);

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

    //setup combo box items
    ui->sites->addItem("Site 1");
    ui->sites->addItem("Site 2");
    ui->sites->addItem("Site 3");
    ui->sites->addItem("Site 4");
    ui->sites->addItem("Site 5");
    ui->sites->addItem("Site 6");
    ui->sites->addItem("Site 7");
    connect(ui->sites, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MainWindow::handleComboBox);

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
    connect(ui->deletePCData, &QAbstractButton::released, this, &MainWindow::deleteSessionFile);

    //other stuff
    ui->reconnect->hide();

    // loads sessions from upload.txt to pc
    device->readAllSessionPrintPc(); 
    
    //setup chart
    QChart *chart = new QChart();
    chart->setTitle("No Signal");
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

void MainWindow::printPc(QString str) {
    ui->pc->append(str);
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
}

void MainWindow::increaseProgresssBar(int amount) {
    ui->progressBar->setValue(ui->progressBar->value() + amount);
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
        if (midSession) {
            device->deleteLatestSession();

            currentRound = 4;
        }
        isPowerOff = true;
        sessionRunning = false;
        midSession =  false;
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
    midSession = true;
    currentRound = 0;
    

    //FRONT END
    sessionRunning = true;
    hideMenus();
    menus[1]->show();
    ui->menu->setDisabled(true);
    ui->upload->setDisabled(true);
    ui->blueLight->setStyleSheet("background-color: rgba(0, 0, 255, 1);");
    ui->eventLog->append("> Session started on:\n" + device->getSessions().last()->getDateTime().toString("yyyy-MM-dd hh:mm:ss"));

    //SESSION STARTS HERE
    stopped = false;
    paused = false;
    ui->sessionTimer->setText("0:29");
    sessionTime = 30;
    ui->pause->setDisabled(false);
    ui->play->setDisabled(false);
    ui->stop->setDisabled(false);
    bool check;

    for (int i = 0; i < 5; i++) {
        ui->eventLog->append("> ========Round " + QString::number(i + 1) + "========");
        if (i == 0) {
            ui->eventLog->append("> Calculating dominant frequencies and baseline before treatment....");
        } else if (i < 5 && i > 0) {
            ui->eventLog->append("> Recalculating dominant frequencies");
        } else {
            ui->eventLog->append("> Recalculating dominant frequencies and baseline after treatment");
        }

        bool temp = true;
        for (int j = 0; j < 10; j++) { // 10 * 500ms = 5 seconds (to reconnect the headset if disconnected)
            if (temp) {
                sessionTimerDecrease();
                temp = false;
            } else {
                temp = true;
            }

            delay(500);

            check = sessionChecks();
            if (check) {
                sessionRunning = false;
                return;
            }
            if (paused) {
                ui->eventLog->append("> Session paused");
                sessionRunning = false;
                while (paused) {
                    delay();
                    check = sessionChecks();
                    if (check) return;
                }
                ui->eventLog->append("> Session resumed");
                sessionRunning = true;
            }
        }

        if (i == 0) {
            ui->eventLog->append("> Baseline before: " + QString::number(device->getSessions().last()->getAvgBefore()));
        }

        if (i < 4) {
            ui->eventLog->append("> Applying treatment");
            sessionTimerDecrease();
            increaseProgresssBar(20);
            delay();

            //green light blink
            ui->greenLight->setStyleSheet("background-color: rgba(0, 255, 0, 1);");
            greenTimer->start(100);
        }


        helpDisplayChart(currentRound, ui->sites->currentIndex());

        check = sessionChecks();
        if (check) {
            sessionRunning = false;
            return;
        }
        if (paused) {
            ui->eventLog->append("> Session paused");
            sessionRunning = false;
            while (paused) {
                delay();
                check = sessionChecks();
                if (check) return;
            }
            ui->eventLog->append("> Session resumed");
            sessionRunning = true;
        }
        currentRound++;

    }

    ui->eventLog->append("> Baseline after: " + QString::number(device->getSessions().last()->getAvgAfter()));
    ui->eventLog->append("> ===Session completed===");

    //SESSION OVER RETURN EVERYTHING BACK
    sessionRunning = false;
    midSession = false;
    currentRound--;
    sessionTimerDecrease();
    increaseProgresssBar(20);
    delay(1000);
    ui->stop->click();
    ui->progressBar->setValue(0);
    
}

void MainWindow::handleSessionHistoryButton() {
    hideMenus();
    menus[2]->show();
    ui->sessionLogs->clear();
    QVector<Session*> sessions = device->getSessions();
    if (sessions.isEmpty()) {
        ui->sessionLogs->append("> No sessions to display.");
        return;
    }
    
    for (int i = 0; i < sessions.size(); i++) {
        ui->sessionLogs->append("Session " + QString::number(i + 1) + ": " + sessions[i]->getDateTime().toString("yyyy-MM-dd hh:mm:ss"));
        ui->sessionLogs->append("------------");
    }
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
    if (midSession) {
        device->deleteLatestSession();
        midSession = false;

        currentRound = 4;
    }
    ui->progressBar->setValue(0);
    ui->sessionTimer->setText("0:00");
    ui->menu->setDisabled(false);
    stopped = true;
    handleMenuButton();
}

void MainWindow::handleUploadButton() {
    ui->upload->setText("Uploading...");
    ui->upload->setDisabled(true);
    print("Uploading data to PC...");
    device->uploadInformation();
    ui->upload->setText("Upload");
    ui->upload->setDisabled(false);
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
    qDebug() << device->getDateTime();
}

void MainWindow::handleReconnectButton() {
    ui->reconnect->hide();
    paused = false;
    ui->eventLog->append("> Headset reconnected. Resuming session");
    redTimer->stop();
    countDown->stop();
    ui->pause->setDisabled(false);
    ui->play->setDisabled(false);
    ui->stop->setDisabled(false);
    ui->blueLight->setStyleSheet("background-color: rgba(0, 0, 255, 1);");
    ui->redLight->setStyleSheet("background-color: rgba(255, 0, 0, 0.2);");
}

void MainWindow::handleCountDown() {
    if (isPowerOff) return;
    if (midSession) {
        device->deleteLatestSession();
        midSession = false;

        currentRound = 4;
    }
    ui->power->click();
}

void MainWindow::batteryDecrease() {
    battery--;
    if (battery == 0) {
        if (midSession) {
            device->deleteLatestSession();
            midSession = false;

            currentRound = 4;
        }
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
void MainWindow::displayChart(QtCharts::QLineSeries *newSeries, int round) {
    QChart *chart = ui->sinewaves->chart();

    // Remove all series from the chart
    QList<QAbstractSeries *> oldSeries = chart->series();
    for (QAbstractSeries *series : oldSeries) {
        chart->removeSeries(series);
    }

    // Add the new series to the chart
    chart->addSeries(newSeries);

    // Recreate default axes to fit the new series automatically
    chart->createDefaultAxes(); 

    // Set the chart title to indicate the round number
    chart->setTitle("Round " + QString::number(round + 1));

    // Optionally force an update to make sure the chart reevaluates its layout
    chart->update();
}

void MainWindow::helpDisplayChart(int round, int site) {
    Session* session = device->getSessions().last();
    QLineSeries *newSeries = session->getRoundSignals()[round][site];
    displayChart(newSeries, round);
}

void MainWindow::handleComboBox(int index) {
    if (device->getSessions().isEmpty()) return;
    helpDisplayChart(currentRound, index);
}

void MainWindow::deleteSessionFile() {
    device->deleteSessionFile();
    ui->pc->clear();
}


