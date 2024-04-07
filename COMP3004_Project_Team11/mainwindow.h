#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QObject>
#include <QDateTime>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class Device;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void batteryDecrease();
    void handlePowerButton();
    void handleMenuButton();
    void handleChargeDeviceButton();
    void handleLowBatteryButton();
    void handleNewSessionButton();
    void handleSessionHistoryButton();
    void handleDateTimeButton();
    void handlePauseButton();
    void handlePlayButton();
    void handleStopButton();
    void handleUploadButton();
    void handleDisconnectHeadsetButton();
    void handleSubmitDateTime();

private:
    //variables
    Ui::MainWindow *ui;
    QTimer *timer;
    int battery = 100;
    std::vector<QWidget*> menus;
    bool isPowerOff = false;
    Device* device;

    //functions
    void hideMenus();
    void turnOffLights();
};
#endif // MAINWINDOW_H
