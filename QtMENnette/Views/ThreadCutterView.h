#pragma once
#include "ThreadCutterModel.h"
#include "ui_MainWindow.h"
#include <QWidget>
#include <qlabel.h>
#include <qfont.h>

class ThreadCutterView : public QWidget
{
	Q_OBJECT
public:
	ThreadCutterView(QWidget* parent = nullptr);
	void render(const ThreadCutterModel& model);
	void failedModule();

private:
	Ui::MainWindow* ui;
};