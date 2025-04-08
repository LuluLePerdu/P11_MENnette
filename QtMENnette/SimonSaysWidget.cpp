#include "SimonSaysWidget.h"

SimonSaysWidget::SimonSaysWidget(QWidget* parent, int length, QLabel* greenLed, QLabel* blueLed, QLabel* redLed, QLabel* yellowLed) :
    QWidget(parent),
    currentIndex(0),
    inputIndex(0),
    m_length(length),
    logic(new SimonSays(m_length)),
    m_greenLed(greenLed),
    m_blueLed(blueLed),
    m_redLed(redLed),
    m_yellowLed(yellowLed),
    group(new QSequentialAnimationGroup)
{
	gameTimer = new QTimer();
	connect(gameTimer, &QTimer::timeout, this, [this]() {
        checkInput(inputIndex);
        if (!checkEnd()) {
            newSequence();
        }
		});
    leds = {m_greenLed, m_blueLed, m_redLed, m_yellowLed};
	getSequence();
}

void SimonSaysWidget::startGame() {
    gameTimer->start(10);
    backupBlink(4, leds);
}

void SimonSaysWidget::checkInput(int storage) {
    Communication& comm = Communication::getInstance();
    
    int msgInput;
    comm.clear();
    msgInput = comm.readMsg(MSG_ID_AR_BUTTON);

    switch (msgInput)
    {
    case 1:
        usrAnswer[storage] = 3;
        inputIndex++;
        break;
    case 2:
        usrAnswer[storage] = 2;
        inputIndex++;
        break;
    case 4:
        usrAnswer[storage] = 1;
        inputIndex++;
        break;
    case 8:
        usrAnswer[storage] = 0;
        inputIndex++;
        break;
    default:
        break;
    }
}

void SimonSaysWidget::newSequence() {
    if (currentIndex >= m_length) {
        gameTimer->stop();
        emit returnToMenuRequested();
    }
    else {
        if (inputIndex >= currentIndex) {
            inputIndex = 0;
            currentIndex++;
            //blinkSequence(currentIndex);
            backupBlink(currentIndex, leds);
        }
    }
}

void SimonSaysWidget::blinkSequence(int currentLed) {
    for (int i = 0; i < currentLed; i++) {
        int currentValue = i;
        int timeOn = i * (500 + 500);
        int timeOff = timeOn + 500;
        QTimer::singleShot(timeOn, this, [this, currentValue]() {
            logic->ledControl(currentValue, true);
            });
        QTimer::singleShot(timeOff, this, [this, currentValue]() {
            logic->ledControl(currentValue, false);
            });
    }
}

void SimonSaysWidget::backupBlink(int currentLed, QList<QLabel*>& labLed) {
    for (int i = 0; i < 4; i++) {
        labLed[i]->hide();
    }

    QApplication::processEvents();

    for (int i = 1; i < currentLed+1; i++) {
        int timeOn = i * (500 + 500);
        int timeOff = timeOn + 500;
        QTimer::singleShot(timeOn, this, [this, &labLed, i]() {
            labLed[sequence[i]]->show();
            });
        QTimer::singleShot(timeOff, this, [this, &labLed, i]() {
            labLed[sequence[i]]->hide();
            });
    }

    int finalTime = (currentLed+1) * 1000;
    QTimer::singleShot(finalTime, this, [labLed]() {
        for (int i = 0; i < 4; i++) {
            labLed[i]->show();
        }
        });
}

bool SimonSaysWidget::checkEnd() {
    if (usrAnswer[inputIndex] != sequence[inputIndex]) {
        gameTimer->stop();
        emit timePenalty(timeOnLoss);
        return true;
    }
    return false;
}

void SimonSaysWidget::getSequence() {
	for (int i = 0; i < m_length; i++) {
		sequence[i] = logic->getElement(i);
	}
}