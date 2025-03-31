#include "SnakeMazeWidget.h"
#include <QPainter>
#include <QKeyEvent>
#include <QTimer>

SnakeMazeWidget::SnakeMazeWidget(QWidget* parent) :
    QWidget(parent),
    gameTimer(new QTimer(this))
{
    logic.initialize();

    connect(gameTimer, &QTimer::timeout, this, &SnakeMazeWidget::updateGame);
    gameTimer->start(1000);

    setFixedSize(500, 500);
}

SnakeMazeWidget::~SnakeMazeWidget()
{
}

void SnakeMazeWidget::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    const char(&maze)[HEIGHT][WIDTH] = logic.getMaze();

    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            QRect rect(x * 20, y * 20, 20, 20);

            if (maze[y][x] == WALL) {
                painter.setBrush(Qt::black);
            }
            else if (maze[y][x] == PLAYER) {
                painter.setBrush(Qt::blue);
            }
            else if (maze[y][x] == OBJECTIVE) {
                painter.setBrush(Qt::green);
            }
            else {
                painter.setBrush(Qt::white);
            }

            painter.drawRect(rect);
        }
    }

    painter.setPen(Qt::black);
    painter.setFont(QFont("Arial", 12));
    painter.drawText(10, 10, "Score: " + QString::number(logic.getScore()));
    painter.drawText(10, 30, "Time left: " + QString::number(logic.getTimeLeft()) + "s");
}

void SnakeMazeWidget::keyPressEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key_Up) {
        logic.changeDirection(0, -1);
    }
    else if (event->key() == Qt::Key_Down) {
        logic.changeDirection(0, 1);
    }
    else if (event->key() == Qt::Key_Left) {
        logic.changeDirection(-1, 0);
    }
    else if (event->key() == Qt::Key_Right) {
        logic.changeDirection(1, 0);
    }
}

void SnakeMazeWidget::updateGame()
{
    logic.movePlayer();
    logic.updateTimer();
    if (!logic.inGame()) {
        gameTimer->stop();
    }
    update(); 
}