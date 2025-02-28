#pragma once
#include "ShakeItModel.h"
#include "ShakeItView.h"

#include "MainMenuView.h"
#include "MainMenuController.h"
#include <iostream>

class ShakeItController
{
public:
	ShakeItController(ShakeItView& view);
	~ShakeItController();
	//void returnToMainMenu();
	void update();
	void run();
	
private:
	ShakeItModel model;
	ShakeItView& view;
};
