#pragma once

//#include <QtWidgets/QWidget>
#include <QtWidgets/qmainwindow.h>
#include "ui_MainWindow.h"
#include "SnakeMazeWidget.h"

#include "CryptographicSequencer.h"
#include "qthread.h"

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
	int totalPenaltyTime = 0;

private slots:
	void on_btnHome_clicked();
	void on_btnSnake_clicked();
	void on_btnLED_clicked();
	void on_btnSimon_clicked();
	void on_btnAccel_clicked();
	void on_btnPoten_clicked();
};