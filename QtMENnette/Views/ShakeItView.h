#pragma once
#include <map>
#include <string>
#include <iostream>
#include "ShakeItModel.h"
using namespace std;

#define RESET "\033[0m"
#define GREEN "\033[32m"
#define RED "\033[31m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#define WHITE "\033[37m"
#define BOLD "\033[1m"
#define UNDERLINE "\033[4m"
#define REVERSE "\033[7m"

class ShakeItView
{
public:
	void render(ShakeItModel& model);

private:
};

