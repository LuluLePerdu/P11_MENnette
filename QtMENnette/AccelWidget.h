#pragma once

#include <QWidget>
#include <QTimer>
#include <QMessageBox>

#include "Communication.h"

class AccelWidget : public QWidget
{
	Q_OBJECT
public:
	AccelWidget(QWidget* parent = nullptr);
	~AccelWidget();
	void startGame();
	void stopGame();
	bool hasWon() { return isShook; }
private:
	QTimer* gameTimer;
	bool isShook = false;
};