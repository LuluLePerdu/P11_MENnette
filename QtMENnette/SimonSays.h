#pragma once
#include "Communication.h"
#include <vector>
#include <QTimer>
#include <QWidget>
#include <QLabel>

using namespace std;
class SimonSays : public QWidget
{
Q_OBJECT
public:
	SimonSays(int length);
	~SimonSays();
	void run(int index);
	void readButtons(vector<int>& ansVector, int index);
	//void run(int button);
	bool getCompleted();
	bool getElement(int index);
	void ledBlink(int index, bool state);
	
private:
	//MainWindow* w = MainWindow::instance();
	void simonSequence();
	void blinkSequence(int index);
	int m_length;
	int seqArray[10];
	bool completed = true;
	int m_currLength = 0;
	QTimer* ledTimer;
	QLabel* labDebug;
};
