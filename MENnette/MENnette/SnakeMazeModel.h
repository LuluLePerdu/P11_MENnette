#pragma once

#include <iostream>
#include <stack>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <windows.h> 
#include <vector>
#include "Color.h"
#include "Clock.h"

using namespace std;

const int WIDTH = 21;
const int HEIGHT = 21;
const char WALL = '#';
const char PLAYER = 'O';
const char EMPTY = ' ';
const char OBJECTIVE = 'X';

class SnakeMazeModel
{
public:
    SnakeMazeModel();

    void setColor(int text, int background);
    int playerX = 1;
    int playerY = 1;
    int directionX = 0;
    int directionY = 0;
    bool ingame = true;
    bool victory = false;

    void buildRandomMaze(int startX, int startY);
    void movePlayer();
    void changeDirection(int dx, int dy);
    void placeObjective();
    bool inGame() const;
    bool victoryEOG() const;
    void initialize();
    void updateTimer();

    const char(&getMaze() const)[HEIGHT][WIDTH];
    int getTimeLeft() const; 
    int getScore() const;

private:
    int score;
    char maze[HEIGHT][WIDTH];
    Clock timerClock;
    int timeLeft = 60;
};