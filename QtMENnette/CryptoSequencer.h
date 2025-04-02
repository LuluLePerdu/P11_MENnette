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
	~CryptoSequencer();

	void initialize();
	std::string updateSequence();


private:
	int target;
};

