#pragma once

//#include <QtWidgets/QWidget>
#include <QtWidgets/qmainwindow.h>
#include "ui_MainWindow.h"
#include "SnakeMazeWidget.h"
#include "ThreadCutterWidget.h"
#include "SimonSaysWidget.h"
#include "ConfigurationWidget.h"

#include "CryptoSequencerWidget.h"
#include "qthread.h"
#include "qlabel.h"
#include "qsignalmapper.h"
#include <QTime>
#include <QElapsedTimer>
#include <QPalette>


class CryptoSequencerWidget;

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
	~MainWindow();
    static MainWindow* instance();
	Ui::MainWindow* getUI() const;

private:
    static MainWindow* w;
    Ui::MainWindow ui;
	SnakeMazeWidget* snakeWidget;
	CryptoSequencerWidget* cryptoWidget;
	ThreadCutterWidget* threadWidget;
	SimonSaysWidget* simonWidget;
	ConfigurationWidget* configWidget;
	int totalPenaltyTime = 0;

	QTimer* debugTimer;
	QElapsedTimer eTimer;
	QTimer* timer;
	QTime countdown;
	bool blink;
	QColor initTimerColor;
	QThread* thread;
	QPalette initTimerPalette;

	void showConfiguration();
	void initLCD(int minutes, int seconds);

private slots:
	void on_btnHome_clicked();
	void on_btnSnake_clicked();
	void on_btnLED_released();
	void on_btnSimon_clicked();
	void on_btnAccel_clicked();
	void on_btnPoten_clicked();
	void on_btnDebug_clicked();

	void ledSetText(bool result);
	void updateTimer();
};