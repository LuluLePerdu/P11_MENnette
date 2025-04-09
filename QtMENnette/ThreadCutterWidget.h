#pragma once

#include <QWidget>
#include <QLabel>
#include <QTimer>
#include <QMessageBox>
#include "ThreadCutter.h"

class ThreadCutterWidget : public QWidget
{
	Q_OBJECT
public:
	explicit ThreadCutterWidget(QWidget* parent = nullptr, int timePenalty);
	~ThreadCutterWidget();
	void startGame();
	int getTimePenalty();
	void setTimePenalty(int time);

signals:
	void timePenalty(int seconds);
	void returnToMenuRequested(bool won);

private:
	void renderText(QLabel* label, QString text);
	void checkEnd();
	bool endOfGame = false;
	QTimer* gameTimer;
	ThreadCutter logic;
	int timeOnLoss = 20;
};