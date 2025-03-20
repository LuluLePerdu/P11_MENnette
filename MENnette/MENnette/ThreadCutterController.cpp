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
    
    int usrInput = 0;
    cout << "** Lisez les instructions fournies attentivement **" << endl;
    cout << "Choix de bouton a appuyer : ";
    cin >> usrInput;
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