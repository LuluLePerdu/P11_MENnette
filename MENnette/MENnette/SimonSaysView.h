#pragma once
#include "SimonSaysModel.h"
#include "Communication.h"

class SimonSaysView
{
public:
	void renderElement(const SimonSaysModel& model, int index);
};