//#include "stdafx.h"
#include "MainWindow.h"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), threadWidget(nullptr), debugTimer(new QTimer(this))
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

	

	threadWidget = new ThreadCutterWidget(this);
	connect(threadWidget, &ThreadCutterWidget::outcomeSubmitted, this, &MainWindow::ledSetText);
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

	cryptoWidget = new CryptoSequencerWidget(this);
	ui.stackedWidget->addWidget(cryptoWidget);
	connect(ui.btnPoten, &QPushButton::clicked, this, &MainWindow::on_btnPoten_clicked);

	initLCD(3, 0);

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

void MainWindow::initLCD(int minutes, int seconds) {
	timer = new QTimer(this);
	countdown = QTime(0, minutes, seconds);

	initTimerColor = QColor(50, 255, 50);
	initTimerPalette = ui.lcdClock->palette();
	initTimerPalette.setColor(initTimerPalette.WindowText, initTimerColor);
	ui.lcdClock->setPalette(initTimerPalette);


	eTimer.start();
	connect(timer, &QTimer::timeout, this, &MainWindow::updateTimer);
	timer->start(100);
	blink = false;
}

void MainWindow::on_btnHome_clicked() {
	ui.stackedWidget->setCurrentIndex(0);
	ui.labDebug->setText("Home");
}

void MainWindow::on_btnSnake_clicked() {
	snakeWidget = new SnakeMazeWidget(21, 21, 10, this); //� remplacer les valeurs par des variables via la config

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
		});

	ui.stackedWidget->setCurrentWidget(snakeWidget);
	ui.labDebug->setText("Snake");
	snakeWidget->startGame();
}

void MainWindow::on_btnLED_clicked() {
	threadWidget = new ThreadCutterWidget(this);
	connect(threadWidget, &ThreadCutterWidget::outcomeSubmitted, this, &MainWindow::ledSetText);
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
	totalPenaltyTime += 10;
}

void MainWindow::on_btnDebug_clicked() {
	ui.stackedWidget->setCurrentIndex(6);
	//ui.labDebug->setText("Debug");
	Communication& comm = Communication::getInstance();
	
	//while (true) {
	int msg = comm.readMsg(MSG_ID_AR_ACCELEROMETER);
	ui.labDebug->setText(QString::number(msg));
	QObject::connect(debugTimer, &QTimer::timeout, this, [&]() {

		int msg = comm.readMsg(MSG_ID_AR_ACCELEROMETER);
		comm.clear();
		//Frame frame = comm.readMsg();
		//int a = frame.data;
		ui.labDebug->setText(QString::number(msg));

		});
	debugTimer->start(100); 
	
}

void MainWindow::ledSetText(bool result) {
	
	if (result) {
		ui.labResult->setText(QString::fromLatin1("Module d�samorc� !"));
	}
	else {
		ui.labResult->setText(QString::fromLatin1("Mauvais bouton !"));
	}
	
}

void MainWindow::updateTimer() {
	int elapsedTime = eTimer.elapsed();
	QTime timeLeft = countdown.addMSecs(-elapsedTime - (totalPenaltyTime * 1000));
	QString formatTime = timeLeft.toString("mm:ss");
	QPalette paletteBlink = ui.lcdClock->palette();
	QColor timerColor;

	if (timeLeft.minute() <= 0 && timeLeft.second() <= 30) {
		blink = !blink;
		timerColor = (blink) ? QColor(255, 50, 50) : QColor(150, 0, 0);
		paletteBlink.setColor(paletteBlink.WindowText, timerColor);
		paletteBlink.setColor(paletteBlink.Light, timerColor);
		//paletteBlink.setColor(paletteBlink.WindowText, timerColor);
		ui.lcdClock->setPalette(paletteBlink);
	
	}

	if ((timeLeft.minute() <= 0 && timeLeft.second() <= 0) || timeLeft.minute() >= 55) {

		timer->stop();
		ui.lcdClock->display("PERDU");
	}
	else {

		ui.lcdClock->display(formatTime);
	}
	
	
}