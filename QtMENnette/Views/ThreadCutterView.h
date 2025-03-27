#pragma once
#include "ThreadCutterModel.h"
#include "MainWindow.h"
#include <QWidget>
#include <qlabel.h>
#include <qfont.h>

class ThreadCutterView : public QWidget
{
	Q_OBJECT
public:
	ThreadCutterView(QLabel* labInstruction, QLabel* labResults);
	void render();
	void moduleState(bool isDeactivated);

private:
	QLabel* labInstruc, *labResult;
};