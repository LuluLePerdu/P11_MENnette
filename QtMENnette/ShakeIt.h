#pragma once
#include <qwidget.h>
#include <qprogressbar.h>
#include "MainWindow.h"
#include "Communication.h"

class ShakeIt : public QWidget
{
public:
	ShakeIt();
	~ShakeIt();

	void initialize();
	int update();

private:
	int target;
};