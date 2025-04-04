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
	bool checkCode();
	


private:
	int target;
	char code[CODE_LENGTH];
	int lastInput=0;
	int m_range = 50;
	int receivedCode[CODE_LENGTH];
	int receivedCodeLength = 0;
};

