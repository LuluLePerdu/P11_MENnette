#pragma once

class ThreadCutterModel
{
public:
	ThreadCutterModel();
	bool getCompleted();
	int getCorrectLED();
	bool getLEDstatus(int index) const;
	void playCutter(int button);
private:
	void LEDscenario();
	bool completed = false;
	bool LEDarray[4];
	int correctLED;
};