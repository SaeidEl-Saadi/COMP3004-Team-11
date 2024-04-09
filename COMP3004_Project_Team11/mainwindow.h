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

    //functions
    void print(QString str);

private slots:
    void greenLightBlink();
    void redLightBlink();
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
    QTimer *greenTimer;
    QTimer *redTimer;
    int battery = 100;
    std::vector<QWidget*> menus;
    bool isPowerOff = false;
    Device* device;
    bool batteryMessage = false;
    int sessionTime = 0;
    bool stopped = false;
    bool paused = false;
    bool redOn = false;

    //functions
    void hideMenus();
    void turnOffLights();
    void delay(int time = 1000);
    void sessionTimerDecrease();
    bool sessionChecks();
};
#endif // MAINWINDOW_H
