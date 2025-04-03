#pragma once
#include "Communication.h"

using namespace std;
class SimonSays
{
public:
	SimonSays();
	void run(int button);
	bool getCompleted();
	void getSequence(int* arr);
	
private:
	//MainWindow* w = MainWindow::instance();
	void simonSequence();
	void blinkSequence(int index);
	int m_length = 10;
	int seqArray[10];
	bool completed = false;

};
