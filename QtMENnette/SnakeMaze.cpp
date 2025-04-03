#include "SnakeMaze.h"

SnakeMaze::SnakeMaze(int width, int height, int duration) :
    WIDTH(width), HEIGHT(height), gameDuration(duration),
    timerStarted(false), hasMoved(false)
{
    allocateMaze();
}

SnakeMaze::~SnakeMaze() {
    deallocateMaze();
}

void SnakeMaze::allocateMaze() {
    maze = new char* [HEIGHT];
    for (int y = 0; y < HEIGHT; y++) {
        maze[y] = new char[WIDTH];
    }
}

void SnakeMaze::deallocateMaze() {
    for (int y = 0; y < HEIGHT; y++) {
        delete[] maze[y];
    }
    delete[] maze;
}

void SnakeMaze::initialize() {
    if (maze != nullptr) {
        deallocateMaze();
    }

    allocateMaze();

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
    timerStarted = false;
    startTime = QDateTime::currentMSecsSinceEpoch();
    timeLeft = gameDuration;
}

void SnakeMaze::startTimer() {
    if (!timerStarted) {
        startTime = QDateTime::currentMSecsSinceEpoch();
        timerStarted = true;
    }
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

void SnakeMaze::movePlayer() {
    if (directionX == 0 && directionY == 0) return;

    int newX = playerX + directionX;
    int newY = playerY + directionY;

    if (maze[newY][newX] == WALL) return;

    if (maze[newY][newX] == OBJECTIVE) {
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

    if (!timerStarted && (dx != 0 || dy != 0)) {
        startTimer();
        hasMoved = true;
    }
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

const char** SnakeMaze::getMaze() const {
    return const_cast<const char**>(maze);
}

void SnakeMaze::updateTimer() {
    if (timerStarted) {
        qint64 now = QDateTime::currentMSecsSinceEpoch();
        timeLeft = gameDuration - (now - startTime) / 1000;
    }
}

int SnakeMaze::getTimeLeft() const {
    return timeLeft;
}
