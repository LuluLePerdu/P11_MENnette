#pragma once
#include "SnakeMazeModel.h"
#include "SnakeMazeView.h"
#include <iostream>


class SnakeMazeController
{
private:
	SnakeMazeModel model;
	SnakeMazeView& view;
public:
	SnakeMazeController(SnakeMazeView& view);
	void returnToMainMenu();
	void update();
	void run();
};