#include "SimonSaysWidget.h"

SimonSaysWidget::SimonSaysWidget(QWidget* parent, int length) : 
	QWidget(parent), 
	currentIndex(0),
    inputIndex(0),
	m_length(length),
	logic(new SimonSays(m_length))
{
	gameTimer = new QTimer();
	connect(gameTimer, &QTimer::timeout, this, [this]() {
        checkInput(inputIndex);
        if (!checkEnd()) {
            newSequence();
        }
		});
	getSequence();
}

void SimonSaysWidget::startGame() {
	gameTimer->start(10);
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
    }
    else {
        if (inputIndex >= currentIndex) {
            inputIndex = 0;
            currentIndex++;
            blinkSequence(currentIndex);
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

bool SimonSaysWidget::checkEnd() {
    if (usrAnswer[inputIndex] != sequence[inputIndex]) {
        gameTimer->stop();
        return true;
    }
    return false;
}

void SimonSaysWidget::getSequence() {
	for (int i = 0; i < m_length; i++) {
		sequence[i] = logic->getElement(i);
	}
}