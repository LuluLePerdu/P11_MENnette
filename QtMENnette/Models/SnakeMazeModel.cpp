#pragma once

#include "SnakeMazeModel.h"
#include <iostream>
#include <stack>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <windows.h> 
#include <vector>
#include "Color.h"

using namespace std;

SnakeMazeModel::SnakeMazeModel()
{
	score = 0;
}

void SnakeMazeModel::initialize()
{
    srand(static_cast<unsigned int>(time(0)));

    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            maze[y][x] = WALL;
        }
    }

    buildRandomMaze(1, 1);

    maze[1][1] = PLAYER;
    placeObjective();
}

void SnakeMazeModel::buildRandomMaze(int startX, int startY) {
    std::stack<std::pair<int, int>> pile;
    pile.push({ startX, startY });
    maze[startY][startX] = EMPTY;

    while (!pile.empty()) {
        auto [x, y] = pile.top();
        std::vector<std::pair<int, int>> voisins;

        if (x > 2 && maze[y][x - 2] == WALL) voisins.push_back({ x - 2, y });
        if (x < WIDTH - 3 && maze[y][x + 2] == WALL) voisins.push_back({ x + 2, y });
        if (y > 2 && maze[y - 2][x] == WALL) voisins.push_back({ x, y - 2 });
        if (y < HEIGHT - 3 && maze[y + 2][x] == WALL) voisins.push_back({ x, y + 2 });

        if (!voisins.empty()) {
            auto [nx, ny] = voisins[rand() % voisins.size()];
            maze[ny][nx] = EMPTY;
            maze[(ny + y) / 2][(nx + x) / 2] = EMPTY;
            pile.push({ nx, ny });
        }
        else {
            pile.pop();
        }
    }

    for (int y = 0; y < HEIGHT; y++) {
        maze[y][0] = maze[y][WIDTH - 1] = WALL;
    }
    for (int x = 0; x < WIDTH; x++) {
        maze[0][x] = maze[HEIGHT - 1][x] = WALL;
    }
}

void SnakeMazeModel::movePlayer()
{
    int newX = playerX + directionX;
    int newY = playerY + directionY;

    if (maze[newY][newX] == WALL) {
        ingame = false;
        return;
    }

    if (maze[newY][newX] == OBJECTIVE) {
		score++;
		ingame = false;
		victory = true;
        return;
    }

    maze[playerY][playerX] = EMPTY;
    playerX = newX;
    playerY = newY;
    maze[playerY][playerX] = PLAYER;
}

void SnakeMazeModel::changeDirection(int dx, int dy)
{
    directionX = dx;
    directionY = dy;
}

void SnakeMazeModel::placeObjective()
{
    int x, y;
    do {
        x = rand() % (WIDTH - 2) + 1;
        y = rand() % (HEIGHT - 2) + 1;
    } while (maze[y][x] != EMPTY || (x == 1 && y == 1));
    maze[y][x] = OBJECTIVE;
}

bool SnakeMazeModel::inGame() const
{
	return ingame;
}

bool SnakeMazeModel::victoryEOG() const
{
	return victory;
}

const char(&SnakeMazeModel::getMaze() const)[HEIGHT][WIDTH]{
    return maze;
}