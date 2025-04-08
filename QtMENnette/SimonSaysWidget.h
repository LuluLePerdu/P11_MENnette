#pragma once

#include "SimonSays.h"
#include <qwidget.h>
#include <qlabel.h>
#include <qtimer.h>
#include <QPropertyAnimation>
#include <QSequentialAnimationGroup>
#include <QApplication>

class SimonSaysWidget : public QWidget
{
	Q_OBJECT
	Q_PROPERTY(QString styleSheet READ styleSheet WRITE setStyleSheet)
public:
	SimonSaysWidget(QWidget* parent = nullptr, int length = 10, QLabel* greenLed = nullptr, 
					QLabel* blueLed = nullptr, QLabel* redLed = nullptr, QLabel* yellowLed = nullptr);
	void startGame();

protected:

private:
	void checkInput(int storage);
	bool checkEnd();
	void getSequence();
	void blinkSequence(int currentLed);
	void backupBlink(int currentLed, QList<QLabel*>& labLed);
	void newSequence();

	int sequence[15];
	int usrAnswer[15];
	int inputIndex;
	int currentIndex;
	int m_length;

	int timeOnLoss = 20;

	SimonSays* logic;
	QTimer* gameTimer;
	QPropertyAnimation* anim;
	QSequentialAnimationGroup* group;
	QLabel* m_greenLed, * m_blueLed, * m_redLed, * m_yellowLed;
	QList<QLabel*> leds;
signals:
	void timePenalty(int seconds);
	void returnToMenuRequested();
};