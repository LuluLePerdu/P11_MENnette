#pragma once
#include "SnakeMazeModel.h"

class SnakeMazeView {
public:
	void setColor(int text, int background);
    void render(const SnakeMazeModel& model);
};