#include "SimonSays.h"
#include <qerrormessage.h>
#include <QMessageBox>

SimonSays::SimonSays() {
    Communication& comm = Communication::getInstance();

    srand(comm.seed);
    simonSequence();
}

void SimonSays::run(int button) {
    Communication& comm = Communication::getInstance();
    int msgInput;
    bool ledArray[8];
    int usrInput;
    int tempArray[10];
    int ansArray[10];
    for (int i = 0; i < m_currLength; i++) {
        /*QMessageBox msg;
        msg.setWindowTitle("AAAAAAAA");
		QString str = QString::number(seqArray[i]);
        msg.setText(str);
        msg.exec();*/
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
                msgInput = comm.readMsg(MSG_ID_AR_BUTTON);
                comm.clear();
            } while (msgInput <= -1);

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
	m_currLength++;
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

void SimonSays::getSequence(int* arr) {
	for (int i = 0; i < 10; i++) {
		arr[i] = this->seqArray[i];
	}
}