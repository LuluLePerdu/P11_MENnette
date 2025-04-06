#include "ThreadCutter.h"
#include <iostream>
using namespace std;

ThreadCutter::ThreadCutter() {
    srand(time(0));
    for (int i = 0; i < 4; i++) {
        ledArray[i] = rand() % 2;
    }
    ledSetup();
}

void ThreadCutter::run() {
    //bool ledArray[8];
    Communication& comm = Communication::getInstance();


    int msgInput;
    comm.clear();
    msgInput = comm.readMsg(MSG_ID_AR_BUTTON);

    /*
    do
    {
        msgInput = comm.readMsg(MSG_ID_AR_BUTTON);
        comm.clear();
    } while (msgInput < 0);
    */

    switch (msgInput)
    {
    case 1:
        checkButton(3);
        break;
    case 2:
        checkButton(2);
        break;
    case 4:
        checkButton(1);
        break;
    case 8:
        checkButton(0);
        break;
    default:
        completed = 2;
        break;
    }
}

// 0 : True, 1 : False, 2 : Pas deviné
int ThreadCutter::checkButton(int button) {
    if (button == correctLed) {
        completed = 0;
    }
    else {
        completed = 1;
    }
	return completed;
}

void ThreadCutter::render() {
    Communication& comm = Communication::getInstance();
    Frame msgLED;
    msgLED.id = MSG_ID_PC_LED;
    bool delStates[8] = { ledArray[0], ledArray[1], ledArray[2], ledArray[3], 0, 0, 0, 0 };
    uint8_t byteMsg = comm.convertBoolsToByte(delStates);
    msgLED.data = byteMsg;
    comm.sendMsg(msgLED);
}

void ThreadCutter::turnOffLed() {
    Communication& comm = Communication::getInstance();
    Frame msgLED;
    msgLED.id = MSG_ID_PC_LED;
    bool delStates[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
    uint8_t byteMsg = comm.convertBoolsToByte(delStates);
    msgLED.data = byteMsg;
    comm.sendMsg(msgLED);
}

int ThreadCutter::getCompleted() {
    return completed;
}

void ThreadCutter::ledSetup() {
    /* old code (fonctionne mais moins complet et clair)
    if (ledArray[0] && ledArray[1] + ledArray[2] + ledArray[3] == 2)
    {
        correctLed = 1;
    }
    else if ((ledArray[0] && ledArray[2] && !ledArray[1] && !ledArray[3])
        || (ledArray[0] && ledArray[1] && ledArray[2] && ledArray[3])) {
        correctLed = 3;
    }
    else if (!ledArray[0] && !ledArray[1] && !ledArray[2] && !ledArray[3]) {
        correctLed = 4;
    }
    else {
        correctLed = 2;
    }
    */
    if ((ledArray[GREEN] && ledArray[BLUE] + ledArray[RED] + ledArray[YELLOW] == 2)
        || (!ledArray[GREEN] && !ledArray[BLUE] && ledArray[RED] && !ledArray[YELLOW]))
    {
        correctLed = GREEN;
    }
    else if ((ledArray[GREEN] && ledArray[RED] && !ledArray[BLUE] && !ledArray[YELLOW])
        || (ledArray[GREEN] && ledArray[BLUE] && ledArray[RED] && ledArray[YELLOW])) {
        correctLed = RED;
    }
    else if ((!ledArray[GREEN] && !ledArray[BLUE] && !ledArray[RED] && !ledArray[YELLOW])
        || (ledArray[BLUE] && ledArray[YELLOW] && !ledArray[GREEN] && !ledArray[RED])) {
        correctLed = YELLOW;
    }
    else if (ledArray[GREEN] + ledArray[BLUE] + ledArray[RED] + ledArray[YELLOW] == 2) {
        correctLed = RED;
    }
    else {
        correctLed = BLUE;
    }
}