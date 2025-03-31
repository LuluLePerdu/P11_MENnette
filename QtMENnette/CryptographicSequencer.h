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

#include "Communication.h"
#include "MainWindow.h"


class CryptographicSequencer : public QWidget
{
public:
	CryptographicSequencer();
	~CryptographicSequencer();
	bool playPot();

private:
	QLabel* labPotSequence = MainWindow::instance()->getUI()->labPotSequence;
};

