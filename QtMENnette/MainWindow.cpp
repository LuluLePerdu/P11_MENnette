#include "MainWindow.h"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), threadWidget(nullptr), debugTimer(new QTimer(this))
{
	ui.setupUi(this);

	this->setFixedSize(1920, 1080);
	player = new QMediaPlayer(this);
	this->setStyleSheet(
		"MainWindow {"
		"   border-image: url(:/MainWindow/Background.png);"
		"}"
	);
	configWidget = new ConfigurationWidget(this);
	ui.stackedWidget->addWidget(configWidget);
	ui.stackedWidget->setCurrentIndex(0);
	Communication& comm = Communication::getInstance();
	if (comm.seed != 0) {
		comm.seed = comm.createSeed();
	}


	connect(ui.btnConfiguration, &QPushButton::clicked, this, &MainWindow::showConfiguration);

	connect(configWidget, &ConfigurationWidget::settingsApplied, this, [this]() {
		ui.stackedWidget->setCurrentIndex(0);
		initLCD(minutes,  secondes);
		Communication& comm = Communication::getInstance();
		comm.sendTime(minutes * 60 + secondes);
		comm.seed = comm.createSeed();
		if (audioOutput) {
			buzzTimer->stop();
			delete audioOutput;
			delete buzzTimer;			
		}
		totalGameWon = 0;
		isInGame = true;
		ui.btnLED->setEnabled(true);
		ui.btnSimon->setEnabled(true);
		ui.btnSnake->setEnabled(true);
		//ui.btnAccel->setEnabled(true);
		ui.btnPoten->setEnabled(true);

		randomGame = (std::rand() % 4) + 1;

		buzzTimer = new QTimer(this);
		audioOutput = new QAudioOutput(this);
		connect(buzzTimer, &QTimer::timeout, this, [this, &comm]() {
			comm.buzz(50);
			qDebug() << "Seed: " << comm.seed;

			if (isInGame) {
			
				player->setSource(QUrl("qrc:/MainWindow/Media/beep_1sec.mp3"));
				player->setAudioOutput(audioOutput);
				audioOutput->setVolume(0.5);
				player->play();

				if (totalGameWon == randomGame && !accelWidget) {
					comm.buzz(255); // motor vibration
					ui.stackedWidget->setCurrentIndex(2);
					accelWidget = new AccelWidget(this);
					ui.stackedWidget->addWidget(accelWidget);
					ui.stackedWidget->setCurrentWidget(accelWidget);
					showPopUps();
					accelWidget->startGame();
				}
				if (totalGameWon == randomGame && accelWidget->hasWon()) {
					comm.buzz(255);
					totalGameWon++;
					//accelWidget->stopGame();
					ui.stackedWidget->removeWidget(accelWidget);
					//delete accelWidget;
					ui.stackedWidget->setCurrentIndex(0);
				}
			}
			});
		buzzTimer->start(1000);
		});

	connect(ui.btnSnake, &QPushButton::clicked, this, &MainWindow::on_btnSnake_clicked);
	showConfiguration();
	
	
}

MainWindow::~MainWindow()
{
	if (snakeWidget) {
		ui.stackedWidget->removeWidget(snakeWidget);
		delete snakeWidget;
	}
	player->stop();
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
	deleteGames();
	ui.stackedWidget->setCurrentWidget(configWidget);
	totalPenaltyTime = 0;

	ui.btnLED->setStyleSheet(
		"QPushButton{"
		"background-color: #1e1e1e;"
		"color: #f2f2f2;"
		"border: 2px solid #770000;"
		"border-radius: 6px;"
		"padding: 10px 16px;"
		"font-family: 'Courier New', monospace;"
		"font-weight: bold;"
		"font-size: 16px;"
		"letter-spacing: 1px;"
		"text-transform: uppercase;"

		"box-shadow:"
		"0 0 8px rgba(255, 0, 0, 0.4),"
		"inset 0 0 4px rgba(255, 0, 0, 0.2);"
		"}"
		"QPushButton:hover{"
		"background-color: #2a0000;"
		"border: 2px solid #aa0000;"
		"box-shadow:"
		"0 0 12px rgba(255, 0, 0, 0.6),"
		"inset 0 0 6px rgba(255, 0, 0, 0.3);"
		"}"

		"QPushButton:pressed{"
		"background-color: #100000;"
		"border: 2px solid #ff0000;"
		"padding-top: 11px;"
		"padding-left: 17px;"
		"box-shadow:"
		"0 0 4px rgba(255, 0, 0, 0.3),"
		"inset 0 0 10px rgba(255, 0, 0, 0.6);"
		"}"
		);

	ui.btnSnake->setStyleSheet(
		"QPushButton{"
		"background-color: #1e1e1e;"
		"color: #f2f2f2;"
		"border: 2px solid #770000;"
		"border-radius: 6px;"
		"padding: 10px 16px;"
		"font-family: 'Courier New', monospace;"
		"font-weight: bold;"
		"font-size: 16px;"
		"letter-spacing: 1px;"
		"text-transform: uppercase;"

		"box-shadow:"
		"0 0 8px rgba(255, 0, 0, 0.4),"
		"inset 0 0 4px rgba(255, 0, 0, 0.2);"
		"}"
		"QPushButton:hover{"
		"background-color: #2a0000;"
		"border: 2px solid #aa0000;"
		"box-shadow:"
		"0 0 12px rgba(255, 0, 0, 0.6),"
		"inset 0 0 6px rgba(255, 0, 0, 0.3);"
		"}"

		"QPushButton:pressed{"
		"background-color: #100000;"
		"border: 2px solid #ff0000;"
		"padding-top: 11px;"
		"padding-left: 17px;"
		"box-shadow:"
		"0 0 4px rgba(255, 0, 0, 0.3),"
		"inset 0 0 10px rgba(255, 0, 0, 0.6);"
		"}"
	);

	ui.btnSimon->setStyleSheet(
		"QPushButton{"
		"background-color: #1e1e1e;"
		"color: #f2f2f2;"
		"border: 2px solid #770000;"
		"border-radius: 6px;"
		"padding: 10px 16px;"
		"font-family: 'Courier New', monospace;"
		"font-weight: bold;"
		"font-size: 16px;"
		"letter-spacing: 1px;"
		"text-transform: uppercase;"

		"box-shadow:"
		"0 0 8px rgba(255, 0, 0, 0.4),"
		"inset 0 0 4px rgba(255, 0, 0, 0.2);"
		"}"
		"QPushButton:hover{"
		"background-color: #2a0000;"
		"border: 2px solid #aa0000;"
		"box-shadow:"
		"0 0 12px rgba(255, 0, 0, 0.6),"
		"inset 0 0 6px rgba(255, 0, 0, 0.3);"
		"}"

		"QPushButton:pressed{"
		"background-color: #100000;"
		"border: 2px solid #ff0000;"
		"padding-top: 11px;"
		"padding-left: 17px;"
		"box-shadow:"
		"0 0 4px rgba(255, 0, 0, 0.3),"
		"inset 0 0 10px rgba(255, 0, 0, 0.6);"
		"}"
	);

	ui.btnPoten->setStyleSheet(
		"QPushButton{"
		"background-color: #1e1e1e;"
		"color: #f2f2f2;"
		"border: 2px solid #770000;"
		"border-radius: 6px;"
		"padding: 10px 16px;"
		"font-family: 'Courier New', monospace;"
		"font-weight: bold;"
		"font-size: 16px;"
		"letter-spacing: 1px;"
		"text-transform: uppercase;"

		"box-shadow:"
		"0 0 8px rgba(255, 0, 0, 0.4),"
		"inset 0 0 4px rgba(255, 0, 0, 0.2);"
		"}"
		"QPushButton:hover{"
		"background-color: #2a0000;"
		"border: 2px solid #aa0000;"
		"box-shadow:"
		"0 0 12px rgba(255, 0, 0, 0.6),"
		"inset 0 0 6px rgba(255, 0, 0, 0.3);"
		"}"

		"QPushButton:pressed{"
		"background-color: #100000;"
		"border: 2px solid #ff0000;"
		"padding-top: 11px;"
		"padding-left: 17px;"
		"box-shadow:"
		"0 0 4px rgba(255, 0, 0, 0.3),"
		"inset 0 0 10px rgba(255, 0, 0, 0.6);"
		"}"
	);

}


void MainWindow::initLCD(int minutes, int seconds) {
	if (timer) {
		timer->stop();
		delete timer;
	}
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
	deleteGames();
	totalGameWon++;
}


void MainWindow::on_btnLED_clicked() {
	if (threadWidget) {
		ui.stackedWidget->removeWidget(threadWidget);
		delete threadWidget;
		threadWidget = nullptr;
	}
	
	threadWidget = new ThreadCutterWidget(this, configWidget->getThreadPenalty());

	this->setStyleSheet(
		"MainWindow {"
		"   border-image: url(:/MainWindow/Media/ThreadCutterInstructionsReasonableSize.jpg);"
		"}"
	);
	Communication& comm = Communication::getInstance();
	connect(threadWidget, &ThreadCutterWidget::timePenalty, this, [this, &comm](int penalty) {
		totalPenaltyTime += penalty;
		elapsedTime = eTimer.elapsed();
		QTime timeLeft = countdown.addMSecs(-elapsedTime - (totalPenaltyTime * 1000));
		comm.sendTime(timeLeft.minute() * 60 + timeLeft.second());
		errorSound();
		});
	
	connect(threadWidget, &ThreadCutterWidget::returnToMenuRequested, this, [this](bool won) {
		this->setStyleSheet(
			"MainWindow {"
			"   border-image: url(:/MainWindow/Background.png);"
			"}"
		);

		ui.stackedWidget->setCurrentIndex(0);

		if (won) {
			ui.btnLED->setEnabled(false);
			totalGameWon++;
			ui.btnLED->setStyleSheet(
				"QPushButton{"
				"background-color: #1e1e1e;"
				"color: #f2f2f2;"
				"border: 2px solid #00FF00;"
				"border-radius: 6px;"
				"padding: 10px 16px;"
				"font-family: 'Courier New', monospace;"
				"font-weight: bold;"
				"font-size: 16px;"
				"letter-spacing: 1px;"
				"text-transform: uppercase;"

				"box-shadow:"
				"0 0 8px rgba(255, 0, 0, 0.4),"
				"inset 0 0 4px rgba(255, 0, 0, 0.2);"
				"}"
				);
		}
		});

	ui.stackedWidget->addWidget(threadWidget);
	ui.stackedWidget->setCurrentIndex(3);
	ui.stackedWidget->setCurrentWidget(threadWidget);

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
		ui.btnSnake->setEnabled(false);
		totalGameWon++;
		ui.btnSnake->setStyleSheet(
			"QPushButton{"
			"background-color: #1e1e1e;"
			"color: #f2f2f2;"
			"border: 2px solid #00FF00;"
			"border-radius: 6px;"
			"padding: 10px 16px;"
			"font-family: 'Courier New', monospace;"
			"font-weight: bold;"
			"font-size: 16px;"
			"letter-spacing: 1px;"
			"text-transform: uppercase;"

			"box-shadow:"
			"0 0 8px rgba(255, 0, 0, 0.4),"
			"inset 0 0 4px rgba(255, 0, 0, 0.2);"
			"}"
		);
	});

	Communication& comm = Communication::getInstance();
	connect(snakeWidget, &SnakeMazeWidget::timePenalty, this, [this, &comm](int penalty) { 
		totalPenaltyTime += penalty;
		elapsedTime = eTimer.elapsed();
		QTime timeLeft = countdown.addMSecs(-elapsedTime - (totalPenaltyTime * 1000));
		comm.sendTime(timeLeft.minute() * 60 + timeLeft.second());
		errorSound();

		});

	snakeWidget->setFocus();
	snakeWidget->setFocusPolicy(Qt::StrongFocus);

	ui.stackedWidget->setCurrentWidget(snakeWidget);
	snakeWidget->startGame();
}

void MainWindow::on_btnSimon_clicked() {

	simonWidget = new SimonSaysWidget(this, configWidget->getSimonLength(), ui.DELVert, ui.DELBleu, ui.DELRouge, ui.DELJaune);

	connect(simonWidget, &SimonSaysWidget::timePenalty, this, [this](int penalty) {

		totalPenaltyTime += penalty;
		errorSound();
		QMessageBox msg;
		msg.setWindowTitle("Simon Says");
		msg.setText("GAME LOST!");
		msg.exec();
		Communication& comm = Communication::getInstance();
		comm.buzz(255);
		elapsedTime = eTimer.elapsed();
		QTime timeLeft = countdown.addMSecs(-elapsedTime - (totalPenaltyTime * 1000));
		comm.sendTime(timeLeft.minute() * 60 + timeLeft.second());
		});
	connect(simonWidget, &SimonSaysWidget::gameWon, this, [this]() {

		ui.btnSimon->setEnabled(false);
		QMessageBox msg;
		msg.setWindowTitle("Simon Says");
		msg.setText("GAME COMPLETED!");
		msg.exec();
		Communication& comm = Communication::getInstance();
		comm.buzz(255);
		totalGameWon++;
		ui.btnSimon->setStyleSheet(
			"QPushButton{"
			"background-color: #1e1e1e;"
			"color: #f2f2f2;"
			"border: 2px solid #00FF00;"
			"border-radius: 6px;"
			"padding: 10px 16px;"
			"font-family: 'Courier New', monospace;"
			"font-weight: bold;"
			"font-size: 16px;"
			"letter-spacing: 1px;"
			"text-transform: uppercase;"

			"box-shadow:"
			"0 0 8px rgba(255, 0, 0, 0.4),"
			"inset 0 0 4px rgba(255, 0, 0, 0.2);"
			"}"
		);
		});
	simonWidget->startGame();
}


//void MainWindow::on_btnAccel_clicked() {
//}


void MainWindow::on_btnPoten_clicked() {
	ui.stackedWidget->setCurrentIndex(5);
	//this->setStyleSheet("MainWindow{ background-image: url(:/MainWindow/Media/paper1.jpg);}");


	if (cryptoWidget) {
		ui.stackedWidget->removeWidget(cryptoWidget);
		delete cryptoWidget;
		cryptoWidget = nullptr;
	}
	cryptoWidget = new CryptoSequencerWidget(this, configWidget->getCryptoRange());

	connect(cryptoWidget, &CryptoSequencerWidget::returnToMenuRequested, this, [this]() {\
		delete cryptoWidget;
		cryptoWidget = nullptr;
		ui.stackedWidget->setCurrentIndex(0);
		ui.btnPoten->setEnabled(false);
		totalGameWon++;
		ui.btnPoten->setStyleSheet(
			"QPushButton{"
			"background-color: #1e1e1e;"
			"color: #f2f2f2;"
			"border: 2px solid #00FF00;"
			"border-radius: 6px;"
			"padding: 10px 16px;"
			"font-family: 'Courier New', monospace;"
			"font-weight: bold;"
			"font-size: 16px;"
			"letter-spacing: 1px;"
			"text-transform: uppercase;"

			"box-shadow:"
			"0 0 8px rgba(255, 0, 0, 0.4),"
			"inset 0 0 4px rgba(255, 0, 0, 0.2);"
			"}"
		);
		});

	Communication& comm = Communication::getInstance();
	connect(cryptoWidget, &CryptoSequencerWidget::timePenalty, this, [this, &comm](int penalty) {
		totalPenaltyTime += penalty;
		elapsedTime = eTimer.elapsed();
		QTime timeLeft = countdown.addMSecs(-elapsedTime - (totalPenaltyTime * 1000));
		comm.sendTime(timeLeft.minute() * 60 + timeLeft.second());
		});

	ui.stackedWidget->addWidget(cryptoWidget);
	ui.stackedWidget->setCurrentWidget(cryptoWidget);

}

void MainWindow::on_btnDebug_clicked() {
	showPopUps();
}

void MainWindow::on_btnQui_clicked() {
	QApplication::quit();
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
	elapsedTime = eTimer.elapsed();
	QTime timeLeft = countdown.addMSecs(-elapsedTime - (totalPenaltyTime * 1000));
	QString formatTime = timeLeft.toString("mm:ss");
	QPalette paletteBlink = ui.lcdClock->palette();
	QColor timerColor;

	if (timeLeft.minute() <= 0 && timeLeft.second() <= 30) {
		blink = !blink;
		timerColor = (blink) ? QColor(255, 50, 50) : QColor(150, 0, 0);
		paletteBlink.setColor(paletteBlink.WindowText, timerColor);
		paletteBlink.setColor(paletteBlink.Light, timerColor);
		ui.lcdClock->setPalette(paletteBlink);
	}

	if (((timeLeft.minute() <= 0 && timeLeft.second() <= 0) || timeLeft.minute() >= 55)) {
		timer->stop();
		showEndGame(QTime(0, 0, 0), false); // lecture seule
	}
	else if (totalGameWon >= 5) {
		timer->stop();
		showEndGame(timeLeft, true);
	}
	else if (false) {
		timer->stop();
		showEndGame(timeLeft, true);
		ui.lcdClock->display("PERDU");
	}
	else {
		ui.lcdClock->display(formatTime);
	}
}

void MainWindow::showEndGame(QTime finalTime, bool victory)
{
	isInGame = false;
	deleteGames();
	player->stop();
	player = new QMediaPlayer(this);
	player->setSource(QUrl("qrc:/MainWindow/Media/jeff.mp3"));
	player->setAudioOutput(audioOutput);
	audioOutput->setVolume(0.15);
	player->setLoops(QMediaPlayer::Once);
	player->play();
	QWidget* current = ui.stackedWidget->currentWidget();
	if (current && current != configWidget && current != ui.pgeMain) {
		ui.stackedWidget->removeWidget(current);
		delete current;
	}

	endGameWidget = new EndGameWidget(finalTime, victory);

	connect(endGameWidget, &EndGameWidget::returnToMainMenu, this, [this]() {
		on_btnHome_clicked();
		if (endGameWidget) {
			ui.stackedWidget->removeWidget(endGameWidget);
			delete endGameWidget;
			endGameWidget = nullptr;
		}
		});

	ui.stackedWidget->addWidget(endGameWidget);
	ui.stackedWidget->setCurrentWidget(endGameWidget);
}

void MainWindow::errorSound() {
	QAudioOutput* outputWrong = new QAudioOutput(this);
	QMediaPlayer* playerWrong = new QMediaPlayer(this);

	connect(playerWrong, &QMediaPlayer::playbackStateChanged, this, [playerWrong, outputWrong](QMediaPlayer::PlaybackState state) {
			if (state == QMediaPlayer::StoppedState) {
				playerWrong->deleteLater();
				outputWrong->deleteLater();
			}
		});

	playerWrong->setSource(QUrl("qrc:/MainWindow/Media/buzzer_wrong.mp3"));
	playerWrong->setAudioOutput(outputWrong);
	outputWrong->setVolume(0.5);
	playerWrong->play();

	//delete playerWrong;
	//delete outputWrong;
}

void MainWindow::deleteGames() {
	if (snakeWidget) {
		snakeWidget->stopGame();
		ui.stackedWidget->removeWidget(snakeWidget);
		delete snakeWidget;
		snakeWidget = nullptr;
	}
	if (simonWidget) {
		ui.stackedWidget->removeWidget(simonWidget);
		delete simonWidget;
		simonWidget = nullptr;
	}
	if (threadWidget) {
		ui.stackedWidget->removeWidget(threadWidget);
		delete threadWidget;
		threadWidget = nullptr;
		this->setStyleSheet(
			"MainWindow {"
			"   border-image: url(:/MainWindow/Background.png);"
			"}"
		);

		QPalette palette = ui.lcdClock->palette();
		palette.setColor(palette.WindowText, QColor(50, 255, 50));
		ui.lcdClock->setPalette(palette);
	}
	if (cryptoWidget) {
		ui.stackedWidget->removeWidget(cryptoWidget);
		delete cryptoWidget;
		cryptoWidget = nullptr;
	}
}

void MainWindow::showPopUps() {
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
		"SECOUE LA MANETTE MAINTENANT!!!",
		"AAAAAAAAAAAAAAAAAAA\nAAAAAAA\nA L'AIDE AAAAAAAAAAAA",
		"VITE!! VITE!! VITE!!",
		"SHAKE! SHAKE! SHAKE!",
		"prend ça molo...",
		"QU'EST-CE QUE TU FAIS?!?!",
		"URGENCE: SECOUE!"
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

	QPixmap rob(":/MainWindow/robus2000.png");
	QPixmap robScaled = rob.scaled(400, 200, Qt::KeepAspectRatio, Qt::SmoothTransformation);
	QMessageBox* msgRob = new QMessageBox();
	msgRob->setWindowTitle(QString("robus..."));
	msgRob->setIconPixmap(robScaled);
	msgRob->move((screenWidth - 400), rand() % (screenHeight - 200));
	msgRob->show();

	QPixmap jp(":/MainWindow/jp.jpg");
	QPixmap jpScaled = jp.scaled(600, 400, Qt::KeepAspectRatio, Qt::SmoothTransformation);
	QMessageBox* msgJP = new QMessageBox();
	msgJP->setWindowTitle(QString("manifestation"));
	msgJP->setIconPixmap(jpScaled);
	//msgJP->move((screenWidth - 400), rand() % (screenHeight - 200));
	msgJP->show();
}