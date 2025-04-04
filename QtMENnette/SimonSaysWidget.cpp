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
	label->setFont(QFont("Cascadia Code", 30));
	label->setText("1234567890");
	//label->setStyleSheet("QLabel { background-color : black; }");
}

SimonSaysWidget::~SimonSaysWidget() {
}

void SimonSaysWidget::updateGame() {
	QString qSeq;
	for (int i = 0; i < 10; i++) {
		//label->setText(QString::number(sequence[i]));
		qSeq += QString::number(sequence[i]) + " ";
	}
	label->setText(qSeq);
	logic->run(0);

}
