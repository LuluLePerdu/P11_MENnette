#include "SimonSaysController.h"
#include "iostream"
#include "MainMenuView.h"
#include "MainMenuController.h"
using namespace std;

SimonSaysController::SimonSaysController(SimonSaysView& v) : view(v) {}

void SimonSaysController::run() {
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
            cin >> ansArray[k];
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