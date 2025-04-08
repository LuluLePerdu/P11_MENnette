#include "SimonSays.h"

SimonSays::SimonSays(int length) : m_length(length), currentRep(0) {
    setSequence();
}

void SimonSays::setSequence() {
    for (int i = 0; i < m_length; i++) {
        seqArray[i] = rand() % 4;
    }
}

bool SimonSays::getCompleted() {
    return completed;
}

void SimonSays::ledControl(int led, bool state) {
    Communication& comm = Communication::getInstance();
    Frame msgLED;
    msgLED.id = MSG_ID_PC_LED;
    bool delStates[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
    int byteMsg;

    if (state) {
        delStates[seqArray[led]] = 1;
        byteMsg = comm.convertBoolsToByte(delStates);
        msgLED.data = byteMsg;
        comm.sendMsg(msgLED);
    }
    else {
        delStates[seqArray[led]] = 0;
        byteMsg = comm.convertBoolsToByte(delStates);
        msgLED.data = byteMsg;
        comm.sendMsg(msgLED);
    }
}

int SimonSays::getElement(int index) {
    return seqArray[index];
}