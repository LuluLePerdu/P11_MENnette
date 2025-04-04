#pragma once
#include "Communication.h"
#include <QTimer>
#include <QWidget>

#define GREEN 0
#define BLUE 1
#define RED 2
#define YELLOW 3

class ThreadCutter
{

public:
	ThreadCutter();
	//~ThreadCutter();
	void run();
	int getCompleted();
	void render();
	void turnOffLed();

private:
	int checkButton(int button);
	void ledSetup();
	int completed = 2;
	bool ledArray[4];
	int correctLed;
	QTimer* timer;
};
