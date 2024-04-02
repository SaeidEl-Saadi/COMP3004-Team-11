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
    }
    ui->battery->clear();
    ui->battery->append(QString::fromStdString(std::to_string(battery) + "%"));
}
