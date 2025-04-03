//#include "stdafx.h"
#include "MainWindow.h"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), threadWidget(nullptr)
{
	ui.setupUi(this);

	this->setStyleSheet(
		"MainWindow {"
		"   background-image: url(:/MainWindow/Background.png);"
		"   background-position: center;"
		"   background-repeat: no-repeat;"
		"   background-attachment: fixed;"
		"   background-size: 50% 50%;"
		"}"
	);

	snakeWidget = new SnakeMazeWidget(21, 21, 35, this); //À remplacer les valeurs par des variables via la config
	ui.stackedWidget->addWidget(snakeWidget);
	connect(ui.btnSnake, &QPushButton::clicked, this, &MainWindow::on_btnSnake_clicked);

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

	threadWidget = new ThreadCutterWidget(this);
	connect(threadWidget, &ThreadCutterWidget::outcomeSubmitted, this, &MainWindow::ledSetText);

	cryptoWidget = new CryptoSequencerWidget(this);
	ui.stackedWidget->addWidget(cryptoWidget);
	//connect(ui.btnPoten, &QPushButton::clicked, this, &MainWindow::on_btnPoten_clicked);
}

MainWindow::~MainWindow()
{
	delete snakeWidget;
	delete threadWidget;
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
}

void MainWindow::on_btnSnake_clicked() {
	ui.stackedWidget->setCurrentWidget(snakeWidget);
	ui.labDebug->setText("Snake");
	snakeWidget->startGame();
}

void MainWindow::on_btnLED_clicked() {
	ui.stackedWidget->setCurrentIndex(3);
	ui.labDebug->setText("LED");
	threadWidget->startGame();
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
	ui.stackedWidget->setCurrentWidget(cryptoWidget);
	ui.labDebug->setText("Poten");
	

}

void MainWindow::ledSetText(bool result) {
	
	if (result) {
		ui.labResult->setText(QString::fromLatin1("Module désamorcé !"));
	}
	else {
		ui.labResult->setText(QString::fromLatin1("Mauvais bouton !"));
	}
	
}
