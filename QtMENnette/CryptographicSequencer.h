#pragma once
#include <iostream>
#include <random>
#include <algorithm>
#include "Communication.h"
#include <thread>
#include <chrono>

using namespace std;



class CryptographicSequencer
{
public:
	CryptographicSequencer();
	~CryptographicSequencer();
	bool playPot();

private:

};

CryptographicSequencer::CryptographicSequencer()
{
}

CryptographicSequencer::~CryptographicSequencer()
{
}