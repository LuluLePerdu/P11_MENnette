#include "ThreadCutterView.h"
#include "Communication.h"
#include <iostream>
using namespace std;

void ThreadCutterView::render(const ThreadCutterModel& model) {
    
    cout << "Diode Rouge (1) : " << (model.getLEDstatus(0) ? "Allumee" : "Eteinte") << endl;
    cout << "Diode Verte (2) : " << (model.getLEDstatus(1) ? "Allumee" : "Eteinte") << endl;
    cout << "Diode Bleue (3) : " << (model.getLEDstatus(2) ? "Allumee" : "Eteinte") << endl;
    cout << "Diode Jaune (4) : " << (model.getLEDstatus(3) ? "Allumee" : "Eteinte") << endl;
   
    Communication& comm = Communication::getInstance();
    Frame msgLED;
    msgLED.id = MSG_ID_PC_LED;
    bool delStates[8] = { model.getLEDstatus(3), model.getLEDstatus(2), model.getLEDstatus(1), model.getLEDstatus(0), 0, 0, 0, 0 };
    uint8_t byteMsg = comm.convertBoolsToByte(delStates);
    msgLED.data = byteMsg;
    comm.sendMsg(msgLED);
}