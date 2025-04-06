#pragma once
#include "ui_MainWindow.h"

#include "ClockWorker.h"
#include "EndGameWidget.h"
#include "SimonSaysWidget.h"
#include "SnakeMazeWidget.h"
#include "ThreadCutterWidget.h"
#include "ConfigurationWidget.h"
#include <QtWidgets/qmainwindow.h>
#include "CryptoSequencerWidget.h"

#include "qthread.h"
#include "qlabel.h"
#include "qsignalmapper.h"

#include <QTime>
#include <QPalette>
#include <QElapsedTimer>

class CryptoSequencerWidget;

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    ~MainWindow();
    MainWindow(QWidget* parent = nullptr);
    Ui::MainWindow* getUI() const;
    static MainWindow* instance();

private:
    QTimer* timer;
    QTime countdown;
    Ui::MainWindow ui;
    bool blink = false;
    QTimer* debugTimer;
    QTimer* clockTimer;
    QElapsedTimer eTimer;
    static MainWindow* w;
    QColor initTimerColor;
    int totalPenaltyTime = 0;
    QPalette initTimerPalette;
    EndGameWidget* endGameWidget = nullptr; 
    SnakeMazeWidget* snakeWidget = nullptr;
    SimonSaysWidget* simonWidget = nullptr;  
    ThreadCutterWidget* threadWidget = nullptr; 
    ConfigurationWidget* configWidget = nullptr; 
    CryptoSequencerWidget* cryptoWidget = nullptr; 

    void showConfiguration();
    void initLCD(int minutes, int seconds);
    void showEndGame(QTime finalTime, bool victory);

private slots:
    void on_btnHome_clicked();
    void on_btnSnake_clicked();
    void on_btnLED_released();
    void on_btnSimon_clicked();
    void on_btnAccel_clicked();
    void on_btnPoten_clicked();
    void on_btnDebug_clicked();
    void on_btnQuit_clicked();

    void updateTimer();
    void ledSetText(bool result);
};