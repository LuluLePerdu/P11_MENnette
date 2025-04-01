#pragma once
#include <QTime>
#include <QDateTime>

class SnakeMaze {
public:
    static const int WIDTH = 21;
    static const int HEIGHT = 21;
    static const char WALL = '#';
    static const char EMPTY = ' ';
    static const char PLAYER = 'P';
    static const char OBJECTIVE = 'O';

    SnakeMaze();
    void initialize();
    void movePlayer();
    void changeDirection(int dx, int dy);
    void placeObjective();
    bool inGame() const;
    bool victoryEOG() const;
    const char(&getMaze() const)[HEIGHT][WIDTH];
    void updateTimer();
    int getTimeLeft() const;
    int getScore() const;
    int getPlayerX() const { return playerX; }
    int getPlayerY() const { return playerY; }
    int getDirectionX() const { return directionX; }
    int getDirectionY() const { return directionY; }

private:
    void buildRandomMaze(int startX, int startY);
	void startTimer();
    bool timerStarted;
    char maze[HEIGHT][WIDTH];
    int playerX, playerY;
    int directionX, directionY;
    int hasMoved;
    bool ingame;
    bool victory;
    int timeLeft;
    qint64 startTime;
};
