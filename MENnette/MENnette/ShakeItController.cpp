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
			switch (_getch())
			{
			case 'a':
				model.setValue(800);
				break;
			case 'r':
				model.setValue(0);
				break;
			case 27:
				returnToMainMenu();
				break;
			default:
				break;
			}

		}
		view.render(model);
		model.setValue(model.realValue + 50);
		this_thread::sleep_for(std::chrono::milliseconds(100));

	}
	system("cls");
	cout << "Returning to main menu" << endl;
	returnToMainMenu();
}