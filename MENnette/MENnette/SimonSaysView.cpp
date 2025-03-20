#include "SimonSaysView.h"
#include <iostream>
using namespace std;

void SimonSaysView::renderElement(const SimonSaysModel& model, int index) {
    Communication& comm = Communication::getInstance();
    Frame msgLED;
    msgLED.id = MSG_ID_PC_LED;
    bool delStates[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
    delStates[index] = 1;
    uint8_t byteMsg = comm.convertBoolsToByte(delStates);
    msgLED.data = byteMsg;
    comm.sendMsg(msgLED);
    cout << model.getElement(index) << " ";
}