#include "SimonSays.h"
#include <qerrormessage.h>
#include <QMessageBox>

SimonSays::SimonSays(int length) : m_length(length) {
    ledTimer = new QTimer(this);
    ledTimer->setSingleShot(true);
    labDebug = new QLabel(this);
    labDebug->setVisible(true);
    labDebug->setGeometry(100, 100, 100, 100);
    
    Communication& comm = Communication::getInstance();

    srand(comm.seed);
    simonSequence();
}

SimonSays::~SimonSays() {
    ledTimer->stop();
    delete ledTimer;
}

/*
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
        msg.exec();
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
*/

void SimonSays::run(int index) {
    for (int i = 0; i < index; i++) {
        int currentValue = i;
        int timeOn = i * (500 + 500);
        int timeOff = timeOn + 500;
        QTimer::singleShot(timeOn, this, [this, currentValue]() {
            ledBlink(currentValue, true);
            });
        QTimer::singleShot(timeOff, this, [this, currentValue]() {
            ledBlink(currentValue, false);
            });
    }
}

void SimonSays::readButtons(vector<int>& ansVector, int index) {
    Communication& comm = Communication::getInstance();

    if (ansVector.size() >= index) {
        for (int i= 0; i < index; i++) {
            if (ansVector.at(i) != seqArray[i]) {
                //cout << endl << "Mauvaise sequence!" << endl;
                completed = false;
            }
        }
        ansVector.clear();
        return;
    }

    int msgInput;
    comm.clear();
    msgInput = comm.readMsg(MSG_ID_AR_BUTTON);

    switch (msgInput)
    {
    case 1:
        ansVector.push_back(3);
        break;
    case 2:
        ansVector.push_back(2);
        break;
    case 4:
        ansVector.push_back(1);
        break;
    case 8:
        ansVector.push_back(0);
        break;
    default:
        break;
    }
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

    ledTimer->singleShot(0, this, [this, index]() {
        ledBlink(index, true);
        });
    ledTimer->singleShot(750, this, [this, index]() {
        ledBlink(index, false);
        });
    /*
    int current = 0;

    QObject::connect(ledTimer, &QTimer::timeout, this, [this, &current]() {
        ledBlink(current);
        current++;
        });

    if (current > index - 1){
        ledTimer->stop();
    }
    ledTimer->start(750);
    */
    

    //Sleep(500);
    //std::this_thread::sleep_for(std::chrono::milliseconds(500));

    
    //cout << seqArray[index] << " ";

    //Sleep(500);
    //std::this_thread::sleep_for(std::chrono::milliseconds(500));
}

void SimonSays::ledBlink(int index, bool state) {
    Communication& comm = Communication::getInstance();
    Frame msgLED;
    msgLED.id = MSG_ID_PC_LED;
    bool delStates[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
    int byteMsg;

    if (state) {
        delStates[seqArray[index]] = 1;
        byteMsg = comm.convertBoolsToByte(delStates);
        msgLED.data = byteMsg;
        comm.sendMsg(msgLED);
        labDebug->setText("LED On");
    }
    else {
        delStates[seqArray[index]] = 0;
        byteMsg = comm.convertBoolsToByte(delStates);
        msgLED.data = byteMsg;
        comm.sendMsg(msgLED);
        labDebug->setText("LED Off");
        ledTimer->stop();
    }
}

bool SimonSays::getElement(int index) {
    return seqArray[index];
}