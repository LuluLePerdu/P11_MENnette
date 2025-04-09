#include "ThreadCutterWidget.h"

ThreadCutterWidget::ThreadCutterWidget(QWidget* parent, int timePenalty) : QWidget(parent), timeOnLoss(timePenalty)
{
	gameTimer = new QTimer(this);

	connect(gameTimer, &QTimer::timeout, this, [this]() {
		logic.run();
		checkEnd();
		});

	startGame();
}

ThreadCutterWidget::~ThreadCutterWidget() {
	logic.turnOffLed();
}

void ThreadCutterWidget::startGame() {
	logic.turnOffLed();
	logic.render();

	gameTimer->start(10);
}

void ThreadCutterWidget::checkEnd() {
	if (logic.getCompleted() != 2) {
		gameTimer->stop();
		logic.turnOffLed();

		if (logic.getCompleted() == 0) {
			QMessageBox msg;
			msg.setWindowTitle("LED GAME");
			msg.setText("GAME COMPLETED!");
			msg.exec();
			emit returnToMenuRequested(true);

		}
		else {
			QMessageBox msg;
			msg.setWindowTitle("LED GAME");
			msg.setText("WRONG LED!");
			msg.exec();
			emit timePenalty(timeOnLoss);
			emit returnToMenuRequested(false);
		}
	}
}

void ThreadCutterWidget::renderText(QLabel* label, QString text) {
	label->setText(text);
	label->setVisible(true);
}

int ThreadCutterWidget::getTimePenalty() {
	return timeOnLoss;
}

void ThreadCutterWidget::setTimePenalty(int time) {
	timeOnLoss = time;
}