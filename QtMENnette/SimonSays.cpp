#include "SimonSays.h"

SimonSays::SimonSays() {
    srand(time(0));
    simonSequence();
}

void SimonSays::run(int button) {
    Communication& comm = Communication::getInstance();
    int msgInput;
    bool ledArray[8];
    int usrInput;
    int tempArray[10];
    int ansArray[10];
    for (int i = 0; i < 10; i++) {
        tempArray[i] = seqArray[i];
        //system("cls");

        for (int j = 0; j < i + 1; j++) {
            blinkSequence(j);
        }
        //Label?
        cout << endl << "Repetez : ";

        for (int k = 0; k < i + 1; k++) {
            //cin >> ansArray[k];
            do
            {
                comm.clear();
                msgInput = comm.readMsg(MSG_ID_AR_BUTTON);
            } while (msgInput == -1);

            switch (msgInput)
            {
            case 1:
                ansArray[k] = 3;
                break;
            case 2:
                ansArray[k] = 2;
                break;
            case 4:
                ansArray[k] = 1;
                break;
            case 8:
                ansArray[k] = 0;
                break;
            default:
                break;
            }
        }
        for (int l = 0; l < i + 1; l++) {
            if (ansArray[l] != tempArray[l]) {
                //Label
                cout << endl << "Mauvaise sequence!" << endl;
                return;
            }
        }
    }
    //Label
    cout << endl << "Module desamorce." << endl;
}

bool SimonSays::getCompleted() {
    return completed;
}

void SimonSays::simonSequence() {
    for (int i = 0; i < 10; i++) {
        seqArray[i] = rand() % 4;
    }
}

void SimonSays::blinkSequence(int index) {
    Communication& comm = Communication::getInstance();
    Frame msgLED;
    msgLED.id = MSG_ID_PC_LED;
    bool delStates[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };

    delStates[seqArray[index]] = 1;
    int byteMsg = comm.convertBoolsToByte(delStates);
    msgLED.data = byteMsg;
    comm.sendMsg(msgLED);

    Sleep(500);

    delStates[seqArray[index]] = 0;
    byteMsg = comm.convertBoolsToByte(delStates);
    msgLED.data = byteMsg;
    comm.sendMsg(msgLED);
    //cout << seqArray[index] << " ";

    Sleep(500);
}