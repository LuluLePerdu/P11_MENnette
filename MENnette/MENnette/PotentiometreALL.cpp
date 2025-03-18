#include "PotentiometreALL.h"

bool playPot() {
    Communication comm;
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

    bool isOver = false;
    float usrInput, distance;
    char outputCode[10];

    while (!isOver) {
        // cout << "Entrez un nombre (0-255) : ";
        // cin >> usrInput;
        usrInput = comm.readMsg();
        if (usrInput < 0) {
            cout << "Erreur d'entreé";
            system("pause");
        } else {
            int distance = 10 * abs(target - usrInput) / 128;
            if (distance > 10) distance = 10;
            // cout << "Base 10 distance : " << distance << endl;
            if (distance == 0) {
                isOver = true;
                for (int i = 0; i < 10; i++) {
                    outputCode[i] = code[i];
                }
                for (int i = 0; i < 10; i++) {
                    cout << outputCode[i];
                }
                system("pause");
            }
            else {
                // cout << "nbchar : " << distance << endl;
                for (int i = 0; i < distance; i++) {
                    outputCode[i] = characters[rand() % 44];
                }
                for (int i = distance; i < 10; i++) {
                    outputCode[i] = code[i];
                }
                //shuffle(begin(outputCode), end(outputCode), randomEngine());
                shuffle(begin(outputCode), end(outputCode), randomEngine);
                for (int i = 0; i < 10; i++) {
                    cout << outputCode[i];
                }
                cout << endl;
                // system("pause");
            }
        }

        system("cls");
    }

    return true;

}