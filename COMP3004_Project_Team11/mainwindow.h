#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QObject>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

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

private:
    //variables
    Ui::MainWindow *ui;
    QTimer *timer;
    int battery = 100;
    std::vector<QWidget*> menus;
    bool isPowerOff = false;

    //functions
    void hideMenus();
};
#endif // MAINWINDOW_H
