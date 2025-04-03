#pragma once

#include <QWidget>
#include "ThreadCutter.h"

class ThreadCutterWidget : public QWidget
{
	Q_OBJECT
public:
	explicit ThreadCutterWidget(QWidget* parent = nullptr);
	void startGame();

signals:
	void outcomeSubmitted(bool outcome);
	void timePenalty(int seconds);

private:
	ThreadCutter logic;
	int timeOnLoss = 20;
};