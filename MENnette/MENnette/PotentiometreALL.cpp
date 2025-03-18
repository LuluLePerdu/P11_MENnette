#include <iostream>
#include <random>
#include <random>
using namespace std;

bool playPot() {
    char characters[] = "!@±/£$¢%¤?¬&¦*()=+#|\\*-[]^¨<>}{`;:,.'";
    char digits[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };
    int target = (rand() % 255);
    int seed = time(0);
    default_random_engine randomEngine(seed);
    cout << "Target : " << target << endl;
    char code[10];
    for (int i = 0; i < 10; i++) {
        code[i] = digits[rand() % 9];
    }

    bool isOver = false;
    float usrInput, distance;
    char tempArray[10];

    while (!isOver) {
        cout << "Entrez un nombre (0-255) : ";
        cin >> usrInput;
        distance = abs(target - usrInput);
        int distanceTen = 10 * distance / 128;
        if (distanceTen > 10) distanceTen = 10;
        cout << "Base 10 distance : " << distanceTen << endl;
        if (distanceTen == 0) {
            isOver = true;
        }
        else {
            cout << "nbchar : " << distanceTen << endl;
            for (int i = 0; i < distanceTen; i++) {
                tempArray[i] = characters[rand() % 44];
            }
            for (int i = distanceTen; i < 10; i++) {
                tempArray[i] = code[i];
            }
            shuffle(begin(tempArray), end(tempArray), randomEngine());
            for (int i = 0; i < 10; i++) {
                cout << tempArray[i];
            }
            cout << endl;
            system("pause");
        }

        system("cls");
    }

    return true;

}