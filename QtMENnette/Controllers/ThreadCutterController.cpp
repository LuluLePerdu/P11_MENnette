#include "ThreadCutterController.h"
#include "MainMenuView.h"
#include "MainMenuController.h"
#include <iostream>
using namespace std;

ThreadCutterController::ThreadCutterController(ThreadCutterView& v) : view(v) {
    //system("cls");
    view.render();
}

void ThreadCutterController::run() {
    int usrInput = 0;
    cout << "** Lisez les instructions fournies attentivement **" << endl;
    cout << "Choix de bouton a appuyer : ";
    cin >> usrInput;
    model.playCutter(usrInput);
    if (model.getCompleted()) {
        cout << endl << "Module desamorce." << endl;
        view.moduleState(true);
        system("pause");
        returnToMainMenu();
    }
    else {
        cout << endl << "Mauvais bouton!" << endl;
        view.moduleState(false);
        system("pause");
        returnToMainMenu();
    }
}

void ThreadCutterController::returnToMainMenu() {
    MainMenuView menuView;
    MainMenuController menuController(menuView);
    menuController.run();
}