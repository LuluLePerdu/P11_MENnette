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
    explicit SnakeMazeWidget(QWidget* parent = nullptr);
    void startGame();
    ~SnakeMazeWidget();

signals:
    void returnToMenuRequested();

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

    bool isAnimating = false;
    QPointF prevPlayerPos;
    QTime animationStartTime;
    float animationDuration = 0.15f;
};
