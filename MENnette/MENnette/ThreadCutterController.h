#pragma once
#include "ThreadCutterModel.h"
#include "ThreadCutterView.h"
#include "Communication.h"

class ThreadCutterController
{
public:
	ThreadCutterController(ThreadCutterView& view);
	void run();
	void returnToMainMenu();

private:
	ThreadCutterModel model;
	ThreadCutterView& view;
};