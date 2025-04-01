#include "SnakeMaze.h"
#include <stack>
#include <cstdlib>
#include <ctime>

SnakeMaze::SnakeMaze() : score(0) {}

void SnakeMaze::initialize()
{
    srand(static_cast<unsigned int>(time(0)));
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            maze[y][x] = WALL;
        }
    }
    buildRandomMaze(1, 1);
    playerX = playerY = 1;
    directionX = directionY = 0;
    maze[playerY][playerX] = PLAYER;
    placeObjective();
    ingame = true;
    victory = false;
    score = 0;
    startTime = QDateTime::currentMSecsSinceEpoch();
    timeLeft = 60;
}

void SnakeMaze::buildRandomMaze(int startX, int startY) {
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

void SnakeMaze::movePlayer()
{
    int newX = playerX + directionX;
    int newY = playerY + directionY;

    if (maze[newY][newX] == WALL) {
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

void SnakeMaze::changeDirection(int dx, int dy)
{
    directionX = dx;
    directionY = dy;
}

void SnakeMaze::placeObjective()
{
    int x, y;
    do {
        x = rand() % (WIDTH - 2) + 1;
        y = rand() % (HEIGHT - 2) + 1;
    } while (maze[y][x] != EMPTY || (x == 1 && y == 1));
    maze[y][x] = OBJECTIVE;
}

bool SnakeMaze::inGame() const
{
    return ingame;
}

bool SnakeMaze::victoryEOG() const
{
    return victory;
}

const char(&SnakeMaze::getMaze() const)[HEIGHT][WIDTH]{
    return maze;
}

void SnakeMaze::updateTimer() {
    qint64 now = QDateTime::currentMSecsSinceEpoch();
    timeLeft = 60 - (now - startTime) / 1000;
}

int SnakeMaze::getTimeLeft() const {
    return timeLeft;
}

int SnakeMaze::getScore() const {
    return score;
}
