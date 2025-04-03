#pragma once

//#include <QtWidgets/QWidget>
#include <QtWidgets/qmainwindow.h>
#include "ui_MainWindow.h"
#include "SnakeMazeWidget.h"
#include "ThreadCutterWidget.h"

#include "CryptoSequencerWidget.h"
#include "qthread.h"
#include "qlabel.h"
#include "qsignalmapper.h"

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
	int totalPenaltyTime = 0;

private slots:
	void on_btnHome_clicked();
	void on_btnSnake_clicked();
	void on_btnLED_clicked();
	void on_btnSimon_clicked();
	void on_btnAccel_clicked();
	void on_btnPoten_clicked();

	void ledSetText(bool outcome);
};