#include "ThreadCutterView.h"
#include "Communication.h"
#include <iostream>
using namespace std;

void ThreadCutterView::render(const ThreadCutterModel& model) {
    
    cout << "Diode Verte (0) : " << (model.getLEDstatus(0) ? "Allumee" : "Eteinte") << endl;
    cout << "Diode Bleue (1) : " << (model.getLEDstatus(1) ? "Allumee" : "Eteinte") << endl;
    cout << "Diode Rouge (2) : " << (model.getLEDstatus(2) ? "Allumee" : "Eteinte") << endl;
    cout << "Diode Jaune (3) : " << (model.getLEDstatus(3) ? "Allumee" : "Eteinte") << endl;
   
    Communication& comm = Communication::getInstance();
    Frame msgLED;
    msgLED.id = MSG_ID_PC_LED;
    bool delStates[8] = { model.getLEDstatus(0), model.getLEDstatus(1), model.getLEDstatus(2), model.getLEDstatus(3), 0, 0, 0, 0 };
    uint8_t byteMsg = comm.convertBoolsToByte(delStates);
    msgLED.data = byteMsg;
    comm.sendMsg(msgLED);
}