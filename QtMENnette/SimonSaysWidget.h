#pragma once

#include "SimonSays.h"
#include <qwidget.h>
#include <qlabel.h>
#include <qtimer.h>
#include <QPropertyAnimation>
#include <QSequentialAnimationGroup>
#include <QApplication>

class SimonSaysWidget : public QWidget
{
    Q_OBJECT
        Q_PROPERTY(QString styleSheet READ styleSheet WRITE setStyleSheet)
public:
    SimonSaysWidget(QWidget* parent = nullptr, int length = 10, QLabel* greenLed = nullptr,
        QLabel* blueLed = nullptr, QLabel* redLed = nullptr, QLabel* yellowLed = nullptr);
    void startGame();
    void stopGame();
    void getSequence();

protected:

private:
    void checkInput();
    bool checkSequence();
    void showSequence();
    void processUserInput(int button);
    void resetUserInput();
    void gameOver(bool won);

    int sequence[15];
    int userInput[15];
    int inputIndex;
    int sequenceLength;
    int currentLevel;
    bool isShowingSequence;
    bool isWaitingForInput;

    int timeOnLoss = 20;
    int blinkDuration = 500;

    SimonSays* logic;
    QTimer* gameTimer;
    QTimer* sequenceTimer;
    QLabel* m_greenLed;
    QLabel* m_blueLed;
    QLabel* m_redLed;
    QLabel* m_yellowLed;
    QList<QLabel*> leds;

signals:
    void timePenalty(int seconds);
    void returnToMenuRequested();
    void gameWon();
};