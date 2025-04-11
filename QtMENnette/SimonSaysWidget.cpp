#include "SimonSaysWidget.h"

SimonSaysWidget::SimonSaysWidget(QWidget* parent, int length, QLabel* greenLed, QLabel* blueLed, QLabel* redLed, QLabel* yellowLed) :
    QWidget(parent),
    currentLevel(0),
    inputIndex(0),
    sequenceLength(length),
    isShowingSequence(false),
    isWaitingForInput(false),
    logic(new SimonSays(sequenceLength)),
    m_greenLed(greenLed),
    m_blueLed(blueLed),
    m_redLed(redLed),
    m_yellowLed(yellowLed)
{
    gameTimer = new QTimer(this);
    connect(gameTimer, &QTimer::timeout, this, &SimonSaysWidget::checkInput);

    sequenceTimer = new QTimer(this);
    sequenceTimer->setSingleShot(true);

    leds = { m_greenLed, m_blueLed, m_redLed, m_yellowLed };
    getSequence();
}

void SimonSaysWidget::startGame() {
    currentLevel = 1;
    resetUserInput();
    showSequence();
}

void SimonSaysWidget::stopGame() {
    gameTimer->stop();
    sequenceTimer->stop();
}

void SimonSaysWidget::checkInput() {
    if (!isWaitingForInput) return;

    Communication& comm = Communication::getInstance();
    comm.clear();
    int msgInput = comm.readMsg(MSG_ID_AR_BUTTON);

    if (msgInput > 0) {
        comm.buzz(80);
        processUserInput(msgInput);
    }
}

void SimonSaysWidget::processUserInput(int button) {
    int pressedButton = -1;

    switch (button) {
    case 1: 
        pressedButton = 3; 
        break;  
    case 2: 
        pressedButton = 2; 
        break;  
    case 4: 
        pressedButton = 1; 
        break;
    case 8: 
        pressedButton = 0; 
        break;  
    default: return;
    }

    //leds[pressedButton]->setStyleSheet("background-color: white;");

    userInput[inputIndex] = pressedButton;
    inputIndex++;

    if (inputIndex >= currentLevel) {
        isWaitingForInput = false;
        if (checkSequence()) {
            if (currentLevel >= sequenceLength) {
                gameOver(true);
            }
            else {
                currentLevel++;
                resetUserInput();
                QTimer::singleShot(1000, this, &SimonSaysWidget::showSequence);
            }
        }
        else {
            gameOver(false);
        }
    }
}

void SimonSaysWidget::showSequence() {
    isShowingSequence = true;
    isWaitingForInput = false;

    for (int i = 0; i < 4; i++) {
        leds[i]->hide();
    }
    QApplication::processEvents();

    for (int i = 0; i < currentLevel; i++) {
        int ledIndex = sequence[i];
        QTimer::singleShot(i * (blinkDuration + 200), this, [this, ledIndex]() {
            leds[ledIndex]->show();
            QApplication::processEvents();
            });
        QTimer::singleShot(i * (blinkDuration + 200) + blinkDuration, this, [this, ledIndex]() {
            leds[ledIndex]->hide();
            QApplication::processEvents();
            });
    }

    QTimer::singleShot(currentLevel * (blinkDuration + 200), this, [this]() {
        for (int i = 0; i < 4; i++) {
            leds[i]->show();
        }
        isShowingSequence = false;
        isWaitingForInput = true;
        inputIndex = 0;
        gameTimer->start(10);
        });
}

bool SimonSaysWidget::checkSequence() {
    for (int i = 0; i < currentLevel; i++) {
        if (userInput[i] != sequence[i]) {
            return false;
        }
    }
    return true;
}

void SimonSaysWidget::resetUserInput() {
    inputIndex = 0;
    for (int i = 0; i < 15; i++) {
        userInput[i] = -1;
    }
}

void SimonSaysWidget::gameOver(bool won) {
    stopGame();
    if (won) {
        emit gameWon();
    }
    else {
        emit timePenalty(timeOnLoss);
    }
    emit returnToMenuRequested();

}

void SimonSaysWidget::getSequence() {
    for (int i = 0; i < sequenceLength; i++) {
        sequence[i] = logic->getElement(i);
    }
}