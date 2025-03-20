#include "SimonSaysController.h"
#include "iostream"
#include "MainMenuView.h"
#include "MainMenuController.h"
using namespace std;

SimonSaysController::SimonSaysController(SimonSaysView& v) : view(v) {}

void SimonSaysController::run() {
    Communication& comm = Communication::getInstance();
    uint8_t msgInput;
    bool ledArray[8];
    int usrInput;
    system("cls");
    int tempArray[10];
	int ansArray[10];
    for (int i = 0; i < 10; i++) {
        tempArray[i] = model.getElement(i);
        system("cls");

        for (int j = 0; j < i + 1; j++) {
            view.renderElement(model, j);
        }
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
                ansArray[k] = 0;
                break;
            case 2:
                ansArray[k] = 1;
                break;
            case 4:
                ansArray[k] = 2;
                break;
            case 8:
                ansArray[k] = 3;
                break;
            default:
                break;
            }
        }
        for (int l = 0; l < i + 1; l++) {
            if (ansArray[l] != tempArray[l]) {
                cout << endl << "Mauvaise sequence!" << endl;
                system("pause");
                returnToMainMenu();
            }
        }
    }
    cout << endl << "Module desamorce." << endl;
    system("pause");
    returnToMainMenu();
}

void SimonSaysController::returnToMainMenu() {
    MainMenuView menuView;
    MainMenuController menuController(menuView);
    menuController.run();
}