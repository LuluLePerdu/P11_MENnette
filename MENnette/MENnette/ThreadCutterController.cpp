#include "ThreadCutterController.h"
#include "MainMenuView.h"
#include "MainMenuController.h"
#include <iostream>
#include <typeinfo>
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

    int msgInput;
	comm.clear();
    do
    {
        msgInput = comm.readMsg(MSG_ID_AR_BUTTON);
		//cout << msgInput;
		//cout << endl << typeid(msgInput).name() << endl;
        comm.clear();
    } while (msgInput == -1);

    switch (msgInput)
    {
    case 1:
        model.playCutter(0);
        break;
    case 2:
        model.playCutter(1);
        break;
    case 4:
        model.playCutter(2);
        break;
    case 8:
        model.playCutter(3);
        break;
    default:
        break;
    }

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