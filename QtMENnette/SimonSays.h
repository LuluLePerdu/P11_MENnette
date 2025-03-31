#pragma once
#include <QWidget>
#include <qlabel.h>
#include "MainWindow.h"
#include "Communication.h"

using namespace std;
class SimonSays : public QWidget
{
public:
	SimonSays();
	void run(int button);
	bool getCompleted();
	
private:
	MainWindow* w = MainWindow::instance();
	void simonSequence();
	void blinkSequence(int index);
	int seqArray[10];
	bool completed = false;
};
