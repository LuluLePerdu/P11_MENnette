#pragma once
#include <QWidget>
#include <qlabel.h>
#include "MainWindow.h"
#include "Communication.h"

#define GREEN 0
#define BLUE 1
#define RED 2
#define YELLOW 3

class ThreadCutter : public QWidget
{
public:
	ThreadCutter(QLabel* labInstruction, QLabel* labResults);
	void run(int button);
	bool getCompleted();

private:
	MainWindow* w = MainWindow::instance();
	QLabel* labInstruc = w->getUI()->labInstruc;
	QLabel* labResult = w->getUI()->labResult;
	bool checkButton(int button);
	void render();
	void ledSetup();
	bool completed = false;
	bool ledArray[4];
	int correctLed;
};
