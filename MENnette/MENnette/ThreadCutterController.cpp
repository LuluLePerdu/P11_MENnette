#include "ThreadCutterController.h"
#include <iostream>
using namespace std;

ThreadCutterController::ThreadCutterController(ThreadCutterView& v) : view(v) {
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
    }
    else {
        cout << endl << "Mauvais bouton!" << endl;
    }
}