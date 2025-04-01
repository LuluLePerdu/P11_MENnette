#pragma once
#include <iostream>
#include <random>
#include <chrono>
#include <thread>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <qwidget.h>
#include <qlabel.h>


#include <qerrormessage.h>

#include "Communication.h"
#include "MainWindow.h"

#define CODE_LENGTH 10


class CryptoSequencer : public QObject
{
	Q_OBJECT

public:
	CryptoSequencer();
	~CryptoSequencer();

	void initialize();
	string updateSequence();

public slots:
	bool playPot(QLabel* labPotSequence);

private:
	int target;
};

