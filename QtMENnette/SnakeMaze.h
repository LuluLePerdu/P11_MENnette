#pragma once
#include <QTime>
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
    void changeDirection(int dx, int dy);
    void placeObjective();
    bool inGame() const;
    bool victoryEOG() const;
    const char** getMaze() const;
    void updateTimer();
    int getTimeLeft() const;
    int getPlayerX() const { return playerX; }
    int getPlayerY() const { return playerY; }
    int getDirectionX() const { return directionX; }
    int getDirectionY() const { return directionY; }
    int getGameDuration() const { return gameDuration; }

private:
    void buildRandomMaze(int startX, int startY);
    void startTimer();
    void allocateMaze();
    void deallocateMaze();

    bool timerStarted;
    char** maze;
    int playerX, playerY;
    int directionX, directionY;
    int hasMoved;
    bool ingame;
    bool victory;
    int timeLeft;
    int gameDuration;
    qint64 startTime;
};