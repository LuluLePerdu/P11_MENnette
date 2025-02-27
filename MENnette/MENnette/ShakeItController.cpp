#include "ShakeItController.h"
#include <chrono>
#include <thread>
//#include <windows.h>
#include <conio.h>
#include "common.hpp"

ShakeItController::ShakeItController(ShakeItView& view) : view(view) {

}
ShakeItController::~ShakeItController() {
}
void ShakeItController::update() {
	MainMenuView menuView;
	MainMenuController menuController(menuView);
	menuController.run();
}
void ShakeItController::run() {
	system("cls");
	int inc = 0.0;
	while (true)
	{
		if (_kbhit()) {
			if (_getch() == 27) { //27 = [ESC] key
				break;
			}
		}
		view.render(model);
		model.setValue(inc);
		inc += 50;
		this_thread::sleep_for(std::chrono::milliseconds(300));
	}
	system("cls");
	cout << "Returning to main menu" << endl;
	returnToMainMenu();

}