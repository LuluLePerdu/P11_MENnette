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
	explicit ThreadCutterWidget(QWidget* parent = nullptr);
	~ThreadCutterWidget();
	void startGame();

signals:
	void timePenalty(int seconds);
	void returnToMenuRequested(bool won);

private:
	void renderText(QLabel* label, QString text);
	void checkEnd();
	bool endOfGame = false;
	QTimer* gameTimer;
	QLabel* labIns;
	QLabel* labRes;
	QLabel* labDebug;
	ThreadCutter logic;
	int timeOnLoss = 20;
};