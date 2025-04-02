#include "CryptoSequencer.h"

CryptoSequencer::CryptoSequencer()
{
    

}

CryptoSequencer::~CryptoSequencer()
{
}

void CryptoSequencer::initialize() {
    Communication& comm = Communication::getInstance();
    std::default_random_engine randomEngine(comm.seed);
    target = (std::rand() % 255);
}

std::string CryptoSequencer::updateSequence() {
	Communication& comm = Communication::getInstance();
    char characters[32] = "!@/\\$%?&*()=+#|\\*-[]^<>}{`;:,.'";
    char digits[10] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };

    char code[CODE_LENGTH];
    for (int i = 0; i < 10; i++) {
        code[i] = digits[std::rand() % 10];
    }

    int joyInput = comm.readMsg(MSG_ID_AR_JOYSTICK);
    if (joyInput == 4) {
    //    isOver = true;
    }

    int usrInput = comm.readMsg(MSG_ID_AR_POTENTIOMETER);
    comm.clear();

    bool isOver = false;
    char outputCode[CODE_LENGTH+1] = {0};

    if (usrInput >= 0) {
        int distance = CODE_LENGTH * std::abs(target - usrInput) / 128;
        if (distance > CODE_LENGTH) distance = CODE_LENGTH;

        if (joyInput != -1) {
            //isOver = true;
        }
        else {
            for (int i = 0; i < CODE_LENGTH; i++) {
                outputCode[i] = characters[std::rand() % 32];
            }
            for (int i = 0; i < CODE_LENGTH - distance; i++) {
                outputCode[i] = code[i];
            }
        }
    }
	outputCode[CODE_LENGTH] = '\0';
	return outputCode;
}


/*
bool CryptoSequencer::playPot(QLabel* labPotSequence) {
	initialize();

    char characters[32] = "!@/\\$%?&*()=+#|\\*-[]^<>}{`;:,.'";
    char digits[10] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };

    char code[10];
    for (int i = 0; i < 10; i++) {
        code[i] = digits[std::rand() % 10];
    }

    float usrInput = -1;
    int joyInput = -1;
    bool isOver = false;
    char outputCode[10];
    comm.clear();
    QErrorMessage msg;
    msg.showMessage("AAAAAAAAAA");
	msg.exec();
    while (!isOver) {
		
        //int joyInput = comm.readMsg(MSG_ID_AR_JOYSTICK);
        //if (joyInput == 4) {
        //    isOver = true;
        //}

        //int potInput = comm.readMsg(MSG_ID_AR_POTENTIOMETER);
        //if (potInput >= 0) {
        //    usrInput = potInput;
        //}

        //comm.clear();

        //if (usrInput >= 0) {
        //    int distance = 10 * std::abs(target - usrInput) / 128;
        //    if (distance > 10) distance = 10;

        ////    if (joyInput != -1) {
        ////        //std::cout << "FIN";
        //        comm.clear();
        //        isOver = true;
        //    }
        //    else {
        //        for (int i = 0; i < 10; i++) {
        //            outputCode[i] = characters[std::rand() % 32];
        //        }
        //        for (int i = 0; i < 10 - distance; i++) {
        //            outputCode[i] = code[i];
        //        }
        //        labPotSequence->setText(outputCode);
        //    }
        //}
        break;  
        
    }

    return true;
}*/



