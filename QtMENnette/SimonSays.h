#pragma once
#include "Communication.h"

using namespace std;
class SimonSays
{
public:
	SimonSays(int length);
	int getElement(int position);
	bool getCompleted();
	void ledControl(int led, bool state);

private:
	void setSequence();
	int m_length;
	int seqArray[15];
	bool completed = false;
	int currentRep;
};
