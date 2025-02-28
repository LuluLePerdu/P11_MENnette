#pragma once
#include "ThreadCutterModel.h"
#include "ThreadCutterView.h"

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