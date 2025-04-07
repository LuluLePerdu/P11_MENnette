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
	~SimonSaysWidget();

protected:
	void startGame();

private:
	void checkEnd();
	void runNextStep();
	QTimer* gameTimer;
	QLabel* label;
	SimonSays* logic;
	int sequence[10];
	vector<int> ansArray;
	int timeOnLoss = 20;

	int currentIndex;
	int m_length;
signals:
	void timePenalty(int seconds);
};