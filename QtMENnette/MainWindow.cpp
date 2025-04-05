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
	configWidget = new ConfigurationWidget(this);
	ui.stackedWidget->addWidget(configWidget);
	ui.stackedWidget->setCurrentIndex(0);

	connect(ui.btnConfiguration, &QPushButton::clicked, this, &MainWindow::showConfiguration);

	connect(configWidget, &ConfigurationWidget::settingsApplied, this, [this]() {
		ui.stackedWidget->setCurrentIndex(0);
		});

	threadWidget = new ThreadCutterWidget(this);
	//connect(threadWidget, &ThreadCutterWidget::outcomeSubmitted, this, &MainWindow::ledSetText);

	connect(ui.btnSnake, &QPushButton::clicked, this, &MainWindow::on_btnSnake_clicked);

	//connect(ui.btnPoten, &QPushButton::clicked, this, &MainWindow::on_btnPoten_clicked);

	initLCD(3, 0);

	Communication& comm = Communication::getInstance();
	srand(comm.seed);
}

MainWindow::~MainWindow()
{
	if (snakeWidget) {
		ui.stackedWidget->removeWidget(snakeWidget);
		delete snakeWidget;
	}
}

MainWindow* MainWindow::instance() {
    if (w == NULL) { w = new MainWindow(); }
    return w;
}

Ui::MainWindow* MainWindow::getUI() const
{
	return const_cast<Ui::MainWindow*>(&ui);
}

void MainWindow::showConfiguration()
{
	ui.stackedWidget->setCurrentWidget(configWidget);
	ui.labDebug->setText("Configuration");
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
	snakeWidget->stopGame();
	ui.labDebug->setText("Home");
}

void MainWindow::on_btnLED_released() {
	threadWidget = new ThreadCutterWidget(this);

	connect(threadWidget, &ThreadCutterWidget::timePenalty, this, [this](int penalty) {
		totalPenaltyTime += penalty;
		});

	ui.stackedWidget->addWidget(threadWidget);
	ui.stackedWidget->setCurrentIndex(3);
	ui.stackedWidget->setCurrentWidget(threadWidget);
	ui.labDebug->setText("LED");

}

void MainWindow::on_btnSnake_clicked()
{
	if (snakeWidget) {
		ui.stackedWidget->removeWidget(snakeWidget);
		delete snakeWidget;
		snakeWidget = nullptr;
	}

	snakeWidget = new SnakeMazeWidget(
		configWidget->getMazeWidth(),
		configWidget->getMazeHeight(),
		configWidget->getMazeTime(),
		configWidget->getDifficulty(),
		this
	);

	ui.stackedWidget->addWidget(snakeWidget);

	connect(snakeWidget, &SnakeMazeWidget::returnToMenuRequested, this, [this]() {
		ui.stackedWidget->setCurrentIndex(0);
		if (snakeWidget) {
			snakeWidget->stopGame();
		}
	});

	connect(snakeWidget, &SnakeMazeWidget::timePenalty, this, [this](int penalty) { totalPenaltyTime += penalty; });

	snakeWidget->setFocus();
	snakeWidget->setFocusPolicy(Qt::StrongFocus);

	ui.stackedWidget->setCurrentWidget(snakeWidget);
	ui.labDebug->setText("Snake");
	snakeWidget->startGame();
}

void MainWindow::on_btnSimon_clicked() {
	simonWidget = new SimonSaysWidget(this);
	ui.stackedWidget->addWidget(simonWidget);
	ui.stackedWidget->setCurrentIndex(4);
	ui.stackedWidget->setCurrentWidget(simonWidget);
	ui.labDebug->setText("Simon");
}

void MainWindow::on_btnAccel_clicked() {
	ui.stackedWidget->setCurrentIndex(2);
	ui.labDebug->setText("Accel");
}

void MainWindow::on_btnPoten_clicked() {
	ui.stackedWidget->setCurrentIndex(5);
	
	cryptoWidget = new CryptoSequencerWidget(this);
	ui.stackedWidget->addWidget(cryptoWidget);
	ui.stackedWidget->setCurrentWidget(cryptoWidget);
	ui.labDebug->setText("Poten");
}

void MainWindow::on_btnDebug_clicked() {
	ui.stackedWidget->setCurrentIndex(6);


	Communication& comm = Communication::getInstance();
	std::mt19937 mt(Communication::getInstance().seed);

	int numPopups = 5;
	QScreen* screen = QGuiApplication::primaryScreen();
	QRect screenGeometry = screen->geometry();
	int screenWidth = screenGeometry.width();
	int screenHeight = screenGeometry.height();

	std::uniform_int_distribution<int> xDist(0, screenWidth - 400);
	std::uniform_int_distribution<int> yDist(0, screenHeight - 200);
	std::uniform_int_distribution<int> fontSizeDist(10, 45);

	QStringList messages = {
		"SECOEU LA MANETTE MAINTENANT!!!",
		"AAAAAAAAAAAAAAAAAAA\nAAAAAAA\nA L'AIDE AAAAAAAAAAAA",
		"VITE!! VITE!! VITE!!",
		"SHAKE! SHAKE! SHAKE!",
		"URGENCE: SECOUEZ!"
	};
	std::uniform_int_distribution<int> msgDist(0, messages.size() - 1);

	QStringList fonts = {
		"Comic Sans MS",
		"Impact",
		"Arial Black",
		"Verdana",
		"Times New Roman",
		"Cascadia Code"
	};
	std::uniform_int_distribution<int> fontDist(0, fonts.size() - 1);

	for (int i = 0; i < numPopups; i++) {
		QMessageBox* msg = new QMessageBox();
		msg->setWindowTitle(QString("MESSAGE IMPORTANT"));

		msg->setText(messages[msgDist(mt)]);

		QFont randomFont(fonts[fontDist(mt)], fontSizeDist(mt));
		randomFont.setBold(true);
		msg->setFont(randomFont);

		//msg->setStandardButtons(QMessageBox::NoButton);
		//msg->setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint | Qt::Tool);

		int x = rand() % (screenWidth - 400);
		int y = rand() % (screenHeight - 200);

		msg->move(x, y);
		msg->show();
	}

	QPixmap jp(":/MainWindow/jp.jpg");
	QPixmap jpScaled = jp.scaled(400, 200, Qt::KeepAspectRatio, Qt::SmoothTransformation);
	QMessageBox* msgJP = new QMessageBox();
	msgJP->setWindowTitle(QString("JP"));
	msgJP->setIconPixmap(jpScaled);
	msgJP->show();
	
}

void MainWindow::ledSetText(bool result) {
	
	if (result) {
		ui.labResult->setText(QString::fromLatin1("Module désamorcé !"));
	}
	else {
		ui.labResult->setText(QString::fromLatin1("Mauvais bouton !"));
	}
	ui.labResult->setVisible(true);
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
