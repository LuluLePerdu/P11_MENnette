#include "CryptoSequencer.h"
#include <qmessagebox.h>

CryptoSequencer::CryptoSequencer()
{
	this->initialize();
}

CryptoSequencer::CryptoSequencer(int range)
{
	m_range = range;
    this->initialize();
}

CryptoSequencer::~CryptoSequencer()
{
}

void CryptoSequencer::initialize() {
    Communication& comm = Communication::getInstance();
    std::default_random_engine randomEngine(comm.seed);
    target = (std::rand() % 255);
    char digits[10] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'}; //'A', 'B', 'C', 'D', 'E', 'F'

    for (int i = 0; i < CODE_LENGTH; i++) {

        code[i] = digits[std::rand() % 10];
    }
}

std::string CryptoSequencer::updateSequence() {
	Communication& comm = Communication::getInstance();
    char characters[32] = "!@/\\$%?&*()=+#|\\*-[]^<>}{`;:,.'";

    //char outputCode[CODE_LENGTH+1];
    std::string outputCode(CODE_LENGTH, ' ');
    for (int i = 0; i < 10; i++) {
        outputCode[i] = characters[std::rand() % 32];
    }

    //int joyInput = comm.readMsg(MSG_ID_AR_JOYSTICK);
    //if (joyInput == 4) {
    //    isOver = true;
    //}


    int usrInput = comm.readMsg(MSG_ID_AR_POTENTIOMETER);
    int keyInput = comm.readMsg(MSG_ID_AR_KEYPAD);
    comm.clear();

    bool isOver = false;

    if (usrInput == -2) {
        return "NO CONTROLLER";
    }

    if (usrInput >= 0) { //si pas de mannette mettre a >=-2
        //usrInput = 100;
        //joyInput = -1;
        int distance = static_cast<int>(CODE_LENGTH * std::abs(target - usrInput) / m_range);
        if (distance > CODE_LENGTH) distance = CODE_LENGTH;

        
       
        for (int i = 0; i < CODE_LENGTH - distance; i++) {
            outputCode[i] = code[i];
        }
		lastInput = usrInput;
    }
    else {
        int distance = static_cast<int>(CODE_LENGTH * std::abs(target - lastInput) / m_range);
        if (distance > CODE_LENGTH) distance = CODE_LENGTH;



        for (int i = 0; i < CODE_LENGTH - distance; i++) {
            outputCode[i] = code[i];
        }
    }
    
    //outputCode = std::to_string(usrInput);
    
    if (keyInput >= 0){
		QMessageBox msg;
		msg.setWindowTitle(QString("KEYPAD"));
		msg.setText(QString::number(keyInput));
		msg.show();
        if (checkCode(keyInput)) {
            
			return "CODE OK";
        }
        return to_string(keyInput);
    }
    

	return outputCode;
}

bool CryptoSequencer::checkCode(int keyInput) {
	

	receivedCode[receivedCodeLength] = keyInput;
    receivedCodeLength++;
    if (receivedCodeLength >= CODE_LENGTH) {
		receivedCodeLength--;
        for (int i = 0; i < CODE_LENGTH; i++) {
            if (receivedCode[i] != code[i]) {
                //std::cout << "Mauvaise sequence!" << std::endl;
                receivedCodeLength = 0;
                return false;
            }
        }
		return true;
    }
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



