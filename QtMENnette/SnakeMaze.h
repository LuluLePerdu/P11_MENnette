#pragma once
#include <QTime>
#include <stack>
#include <ctime>
#include <cstdlib>
#include <QDateTime>

class SnakeMaze {
public:
    int WIDTH;
    int HEIGHT;
    static const char WALL = '#';
    static const char EMPTY = ' ';
    static const char PLAYER = 'P';
    static const char OBJECTIVE = 'O';

    SnakeMaze(int width = 21, int height = 21, int gameDuration = 60);
    ~SnakeMaze();
    void initialize();
    void movePlayer();
    void updateTimer();
    bool inGame() const;
    void placeObjective();
    bool victoryEOG() const;
    int getTimeLeft() const;
    const char** getMaze() const;
    void changeDirection(int dx, int dy);
    int getPlayerX() const { return playerX; }
    int getPlayerY() const { return playerY; }
    int getDirectionX() const { return directionX; }
    int getDirectionY() const { return directionY; }
    int getGameDuration() const { return gameDuration; }

private:
    void startTimer();
    void allocateMaze();
    void deallocateMaze();
    void buildRandomMaze(int startX, int startY);

    char** maze;
    int hasMoved;
    bool ingame;
    bool victory;
    int timeLeft;
    int gameDuration;
    qint64 startTime;
    bool timerStarted;
    int playerX, playerY;
    int directionX, directionY;
};