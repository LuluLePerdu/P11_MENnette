#pragma once

#include <iostream>
#include <stack>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <windows.h>
#include <vector>
#include "Clock.h"

using namespace std;

const int WIDTH = 21;
const int HEIGHT = 21;
const char WALL = '#';
const char PLAYER = 'O';
const char EMPTY = ' ';
const char OBJECTIVE = 'X';

class SnakeMaze
{
public:
    SnakeMaze();

    void initialize();
    void buildRandomMaze(int startX, int startY);
    void movePlayer();
    void changeDirection(int dx, int dy);
    void placeObjective();
    void updateTimer();

    bool inGame() const;
    bool victoryEOG() const;

    const char(&getMaze() const)[HEIGHT][WIDTH];
    int getTimeLeft() const;
    int getScore() const;

private:
    int playerX = 1;
    int playerY = 1;
    int directionX = 0;
    int directionY = 0;
    bool ingame = true;
    bool victory = false;

    int score;
    char maze[HEIGHT][WIDTH];
    int timeLeft = 60;
	Clock timerClock;
};
