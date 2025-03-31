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


class CryptographicSequencer : public QObject
{
	Q_OBJECT

public:
	CryptographicSequencer();
	~CryptographicSequencer();

public slots:
	bool playPot(QLabel* labPotSequence);

private:
	//QLabel* labPotSequence;
};

