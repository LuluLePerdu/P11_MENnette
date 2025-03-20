#include "SimonSaysView.h"
#include <iostream>
using namespace std;

void SimonSaysView::renderElement(const SimonSaysModel& model, int index) {
    Communication& comm = Communication::getInstance();
    Frame msgLED;
    msgLED.id = MSG_ID_PC_LED;
    bool delStates[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };

    delStates[model.getElement(index)] = 1;
    uint8_t byteMsg = comm.convertBoolsToByte(delStates);
    msgLED.data = byteMsg;
    comm.sendMsg(msgLED);

    Sleep(500);

    delStates[model.getElement(index)] = 0;
    uint8_t byteMsg = comm.convertBoolsToByte(delStates);
    msgLED.data = byteMsg;
    comm.sendMsg(msgLED);
    cout << model.getElement(index) << " ";
    
    Sleep(1000);
}