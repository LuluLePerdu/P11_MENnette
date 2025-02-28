#pragma once
#include "SimonSaysModel.h"
#include "SimonSaysView.h"

class SimonSaysController 
{
public:
	SimonSaysController(SimonSaysView& v);
	void run();
	void returnToMainMenu();
private:
	SimonSaysModel model;
	SimonSaysView& view;
};