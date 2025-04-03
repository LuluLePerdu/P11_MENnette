#pragma once
#include "Communication.h"

#define GREEN 0
#define BLUE 1
#define RED 2
#define YELLOW 3

class ThreadCutter
{
public:
	ThreadCutter();
	void run();
	bool getCompleted();

private:
	bool checkButton(int button);
	void render();
	void ledSetup();
	bool completed = false;
	bool ledArray[4];
	int correctLed;
};
