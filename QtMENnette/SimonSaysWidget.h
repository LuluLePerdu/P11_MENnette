#pragma once

#include <qwidget.h>
#include <qlabel.h>
#include <qtimer.h>
#include "SimonSays.h"

class SimonSaysWidget : public QWidget
{
	Q_OBJECT
public:
	SimonSaysWidget(QWidget* parent = nullptr);
	~SimonSaysWidget();

protected:
	void updateGame();

private:
	QTimer* gameTimer;
	QLabel* label;
	SimonSays* logic;
	int sequence[10];
};