#pragma once

#include <QWidget>
#include <QTimer>
#include <QTime>
#include <QPointF>
#include "SnakeMaze.h"

class SnakeMazeWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SnakeMazeWidget(int mazeWidth = 21,
        int mazeHeight = 21,
        int gameDuration = 60,
        QWidget* parent = nullptr);

    void startGame();
    void stopGame();
    ~SnakeMazeWidget();

signals:
    void returnToMenuRequested();
    void timePenalty(int seconds);

protected:
    void paintEvent(QPaintEvent* event) override;
    void keyPressEvent(QKeyEvent* event) override;

private slots:
    void updateGame();

private:
    void showResultDialog();

    SnakeMaze logic;
    QTimer* gameTimer;
    QTimer* animationTimer;
    const int cellSize = 20;
    const int hudHeight = 40;
    bool isOvertime = false;
    float pulseScale = 1.0f;
    bool pulseGrowing = true;
    bool isAnimating = false;
    QPointF prevPlayerPos;
    QTime animationStartTime;
    float animationDuration = 0.15f;
};
