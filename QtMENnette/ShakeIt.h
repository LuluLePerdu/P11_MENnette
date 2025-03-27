#pragma once
#include <qwidget.h>
#include <qprogressbar.h>
#include "MainWindow.h"

class ShakeIt : public QWidget
{
public:
	ShakeIt();
	~ShakeIt();

private:
	QProgressBar* prbBargraph = MainWindow::instance()->getUI()->prbBargraph;
};

ShakeIt::ShakeIt()
{
}

ShakeIt::~ShakeIt()
{
}