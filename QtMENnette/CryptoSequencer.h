#pragma once
#include <random>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <string>



#include "Communication.h"
#include "MainWindow.h"

#define CODE_LENGTH 10


class CryptoSequencer {

public:
	CryptoSequencer();
	CryptoSequencer(int range);
	~CryptoSequencer();

	void initialize();
	std::string updateSequence();
	bool checkCode(int keyInput);
	std::string randomizeString(std::string input, float percent);
	std::string getUserCode();
	bool isGameOver() { return isOver; }
	bool wrongCode = false;
	


private:
	int target;
	char code[CODE_LENGTH+1];
	int lastInput=0;
	int m_range = 50;
	char receivedCode[CODE_LENGTH];
	int receivedCodeLength = 0;
	bool isOver = false;
	
};

