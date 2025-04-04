#pragma once

#include <QTime>
#include <QTimer>
#include <QWidget>
#include <QPointF>
#include <QPainter>
#include <QKeyEvent>
#include <QMessageBox>
#include <QPushButton>
#include <QPainterPath>
#include <QLinearGradient>

#include "Communication.h"
#include "ConfigurationWidget.h"
#include "SnakeMaze.h"
#include <cstdlib>

class SnakeMazeWidget : public QWidget
{
    Q_OBJECT
public:
	explicit SnakeMazeWidget(int mazeWidth = 21, int mazeHeight = 21, int gameDuration = 60, ConfigurationWidget::Difficulty difficulty = ConfigurationWidget::NORMAL,
        QWidget* parent = nullptr);
    ~SnakeMazeWidget();

    void stopGame();
    void startGame();

signals:
    void returnToMenuRequested();
    void timePenalty(int seconds);  

protected:
    void paintEvent(QPaintEvent* event) override;
    void keyPressEvent(QKeyEvent* event) override;

private slots:
    void updateGame();

private:
    void handleInputs();
    void showResultDialog();
    void startAnimation(const QPointF& prevPos);

    SnakeMaze logic;
    QTimer* gameTimer;
    int cellSize = 20;
    int hudHeight = 40;


    struct {
        QPointF startPos;
        QPointF endPos;
        QTime startTime;
        bool active = false;
    } currentAnimation;

    QPointF renderPos;
    uint8_t lastJoystickValue = 0;
    float animationDuration;
};