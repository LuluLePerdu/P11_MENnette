#pragma once

class SimonSaysModel
{
public:
	SimonSaysModel();
	int getElement(int index) const;
	bool getCompleted();
private:
	void simonSequence();
	bool completed = false;
	bool seqArray[10];
};