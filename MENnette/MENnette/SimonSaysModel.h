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
	int seqArray[10];
};