#include "CryptographicSequencer.h"


bool CryptographicSequencer::playPot() {
    system("cls");
    Communication& comm = Communication::getInstance();
    char characters[] = "!@±/£$¢%¤?¬&¦*()=+#|\\*-[]^¨<>}{`;:,.'";
    char digits[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };
    int target = (rand() % 255);
    int seed = time(0);
    default_random_engine randomEngine(seed);
    // cout << "Target : " << target << endl;
    char code[10];
    for (int i = 0; i < 10; i++) {
        code[i] = digits[rand() % 9];
    }

    float usrInput = -1;
    int joyInput = -1;
    bool isOver = false;
    float distance;
    char outputCode[10];
    comm.clear();
    while (!isOver) {
        int joyInput = comm.readMsg(MSG_ID_AR_JOYSTICK);
        if (joyInput == 4) {
            isOver = true;
        }

        int potInput = comm.readMsg(MSG_ID_AR_POTENTIOMETER);
        if (potInput >= 0) {
            usrInput = potInput;
        }

        comm.clear();

        if (usrInput >= 0) {
            int distance = 10 * abs(target - usrInput) / 128;
            if (distance > 10) distance = 10;

            if (joyInput != -1) {
                cout << "FIN";
                comm.clear();
                isOver = true;
            }
            else {
                for (int i = 0; i < 10; i++) {
                    outputCode[i] = characters[rand() % 44];
                }
                for (int i = 0; i < 10 - distance; i++) {
                    outputCode[i] = code[i];
                }
                for (int i = 0; i < 10; i++) {
                    cout << outputCode[i];
                }
                cout << " Distance : " << distance;
                cout << "\r";
            }
        }

        this_thread::sleep_for(std::chrono::milliseconds(33));
    }

    return true;
}