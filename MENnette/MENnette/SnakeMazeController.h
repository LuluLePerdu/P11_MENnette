#pragma once
#include "SnakeMazeView.h"
#include "SnakeMazeModel.h"
#include "Clock.h"
#include <conio.h>
#include <thread>

class SnakeMazeController {
public:
    SnakeMazeController(SnakeMazeView& v);
    void run();

private:
    SnakeMazeView& view;
    SnakeMazeModel model;
    Clock gameClock;
    Clock frameClock;

    void returnToMainMenu();
    void displayEndGameMessage(bool victory, int time);
};