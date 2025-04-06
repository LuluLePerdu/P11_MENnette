#include "SimonSaysWidget.h"

SimonSaysWidget::SimonSaysWidget(QWidget* parent, int length) : 
	QWidget(parent),
	gameTimer(new QTimer(this)),
	label(new QLabel(this)),
	logic(new SimonSays(length)),
	m_length(length),
	currentIndex(0)
{
	connect(gameTimer, &QTimer::timeout, this, [this]() {
		logic->readButtons(ansArray, currentIndex);
		checkEnd();
		});


	setFixedSize(5000, 500);
	label->setFont(QFont("Cascadia Code", 30));
	label->setText("1234567890");
	//label->setStyleSheet("QLabel { background-color : black; }");
	startGame();
}

SimonSaysWidget::~SimonSaysWidget() {
}

void SimonSaysWidget::startGame() {
	gameTimer->start(10);
	for (int i = 0; i < m_length; i++) {
		runNextStep();
	}
}

void SimonSaysWidget::runNextStep() {
	if (currentIndex < m_length) {
		logic->run(currentIndex);

		int sequenceTime = currentIndex * (500 + 500) + 1500;

		QTimer::singleShot(sequenceTime, this, [this]() {
			currentIndex++;
			runNextStep();
			});
	}
}

void SimonSaysWidget::checkEnd() {
	if (!logic->getCompleted()) {
		gameTimer->stop();
		label->setText("Perdu!!");
		emit timePenalty(timeOnLoss);
	}
}
/*
void SimonSaysWidget::updateGame() {
	QString qSeq;
	for (int i = 0; i < 10; i++) {
		qSeq += QString::number(sequence[i]) + " ";
	}
	label->setText(qSeq);
}
*/
