#include "ThreadCutterController.h"
#include "MainMenuView.h"
#include "MainMenuController.h"
#include <iostream>
using namespace std;

ThreadCutterController::ThreadCutterController(ThreadCutterView& v) : view(v) {
    system("cls");
    view.render(model);
}

void ThreadCutterController::run() {
    bool ledArray[8];
    Communication& comm = Communication::getInstance();
    cout << "** Lisez les instructions fournies attentivement **" << endl;
    cout << "Choix de bouton a appuyer : ";

    uint8_t msgInput;

    do
    {
        comm.clear();
        msgInput = comm.readMsg(MSG_ID_AR_BUTTON);
    } while (msgInput == -1);

    comm.byteToBoolArray(msgInput, ledArray);
    int usrInput = -1;
    for (int i = 0; i < 4; i++) {
        if (usrInput == -1 && ledArray[i]) {
            usrInput = i;
        }
    }   
    model.playCutter(usrInput);
    if (model.getCompleted()) {
        cout << endl << "Module desamorce." << endl;
        system("pause");
        returnToMainMenu();
    }
    else {
        cout << endl << "Mauvais bouton!" << endl;
        system("pause");
        returnToMainMenu();
    }
}

void ThreadCutterController::returnToMainMenu() {
    MainMenuView menuView;
    MainMenuController menuController(menuView);
    menuController.run();
}