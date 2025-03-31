#include "CryptographicSequencer.h"

bool CryptographicSequencer::playPot(QLabel* labPotSequence) {
    Communication& comm = Communication::getInstance();
    char characters[] = "!@/\\$%?&*()=+#|\\*-[]^<>}{`;:,.'";
    char digits[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };
    int target = (std::rand() % 255);
    int seed = std::time(0);
    std::default_random_engine randomEngine(comm.seed);
    // std::cout << "Target : " << target << std::endl;
    char code[10];
    for (int i = 0; i < 10; i++) {
        code[i] = digits[std::rand() % 10];
    }

    float usrInput = -1;
    int joyInput = -1;
    bool isOver = false;
    char outputCode[11]; // Increase buffer size to 11 to include null-terminator
    comm.clear();
    QErrorMessage msg;
    msg.showMessage("AAAAAAAAAA");
	msg.exec();
    //std::this_thread::sleep_for(std::chrono::milliseconds(3000));
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
        //        outputCode[10] = '\0'; // Ensure null-termination
        //        labPotSequence->setText(outputCode);
        //    }
        //}
        break;  
        
    }

    return true;
}

CryptographicSequencer::CryptographicSequencer()
{
    //labPotSequence = MainWindow::instance()->getUI()->labPotSequence;
}

CryptographicSequencer::~CryptographicSequencer()
{
}
