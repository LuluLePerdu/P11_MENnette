//#include "stdafx.h"
#include "MainWindow.h"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent)
{
	ui.setupUi(this);
	snakeWidget = new SnakeMazeWidget(21, 21, 35, this); //� remplacer les valeurs par des variables via la config
	ui.stackedWidget->addWidget(snakeWidget);

	connect(ui.btnSnake, &QPushButton::clicked, this, &MainWindow::on_btnSnake_clicked);
	connect(snakeWidget, &SnakeMazeWidget::returnToMenuRequested, this, [this]() {
		ui.stackedWidget->setCurrentIndex(0);
		});

	connect(snakeWidget, &SnakeMazeWidget::returnToMenuRequested, this, [this]() {
		ui.stackedWidget->setCurrentIndex(0);
		snakeWidget->stopGame();
		});

	connect(snakeWidget, &SnakeMazeWidget::timePenalty, this, [this](int penalty) {
		totalPenaltyTime += penalty;
		//updateGlobalTimerDisplay();
		});
}

MainWindow::~MainWindow()
{
	delete snakeWidget;
}

MainWindow* MainWindow::instance() {
    if (w == NULL) { w = new MainWindow(); }
    return w;
}

Ui::MainWindow* MainWindow::getUI() const
{
	return const_cast<Ui::MainWindow*>(&ui);
}

void MainWindow::on_btnHome_clicked() {
	ui.stackedWidget->setCurrentIndex(0);
	ui.labDebug->setText("Home");
	OutputDebugString(L"Home\n");
}

void MainWindow::on_btnSnake_clicked() {
	ui.stackedWidget->setCurrentWidget(snakeWidget);
	ui.labDebug->setText("Snake");
	snakeWidget->startGame();
}

void MainWindow::on_btnLED_clicked() {
	ui.stackedWidget->setCurrentIndex(3);
	ui.labDebug->setText("LED");
}

void MainWindow::on_btnSimon_clicked() {
	ui.stackedWidget->setCurrentIndex(4);
	ui.labDebug->setText("Simon");
}

void MainWindow::on_btnAccel_clicked() {
	ui.stackedWidget->setCurrentIndex(2);
	ui.labDebug->setText("Accel");
}

void MainWindow::on_btnPoten_clicked() {
	ui.stackedWidget->setCurrentIndex(5);
	ui.labDebug->setText("Poten");
	

}