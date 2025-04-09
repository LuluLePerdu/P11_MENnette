#include "AccelWidget.h"

AccelWidget::AccelWidget(QWidget* parent) : QWidget(parent)
{
}

AccelWidget::~AccelWidget()
{
	gameTimer->stop();
	delete gameTimer;
}

void AccelWidget::startGame()
{
	gameTimer = new QTimer(this);
	Communication& comm = Communication::getInstance();
	QObject::connect(gameTimer, &QTimer::timeout, this, [this, &comm]() {
		int shake = comm.readMsg(MSG_ID_AR_SHAKED);
		if (shake >= 0) {
			isShook = true;
			comm.buzz(255);
			gameTimer->stop();
			
		}

		});
	gameTimer->start(20);
}
