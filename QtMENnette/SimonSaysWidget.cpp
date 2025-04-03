#include "SimonSaysWidget.h"

SimonSaysWidget::SimonSaysWidget(QWidget* parent) : 
	QWidget(parent),
	gameTimer(new QTimer(this)),
	label(new QLabel(this)),
	logic(new SimonSays())
{

	logic->getSequence(sequence);
	connect(gameTimer, &QTimer::timeout, this, &SimonSaysWidget::updateGame);
	gameTimer->start(100);

	setFixedSize(5000, 500);
	label->setFont(QFont("Cascadia Code", 100));
}

SimonSaysWidget::~SimonSaysWidget() {
}

void SimonSaysWidget::updateGame() {
	for (int i = 0; i < 10; i++) {
		label->setText(QString::number(sequence[i]));
	}
}
