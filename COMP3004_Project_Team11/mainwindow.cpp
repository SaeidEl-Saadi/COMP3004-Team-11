#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    timer = new QTimer(this);
    QObject::connect(timer, &QTimer::timeout, this, &MainWindow::batteryDecrease);
    timer->start(10000);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::batteryDecrease() {
    battery--;
    if (battery == 0) {
        timer->stop();
        return;
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
