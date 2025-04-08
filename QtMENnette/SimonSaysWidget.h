#pragma once

#include <qwidget.h>
#include <qlabel.h>
#include <qtimer.h>
#include "SimonSays.h"

class SimonSaysWidget : public QWidget
{
	Q_OBJECT
public:
	SimonSaysWidget(QWidget* parent = nullptr, int length = 10);
	void startGame();

protected:

private:
	void checkInput(int storage);
	bool checkEnd();
	void getSequence();
	void blinkSequence(int currentLed);
	void newSequence();

	int sequence[15];
	int usrAnswer[15];
	int inputIndex;
	int currentIndex;
	int m_length;

	SimonSays* logic;
	QTimer* gameTimer;
signals:
	void timePenalty(int seconds);
};