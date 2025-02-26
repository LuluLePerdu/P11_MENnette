#include "ShakeItController.h"
#include <chrono>
#include <thread>

ShakeItController::ShakeItController(ShakeItView& view) : view(view) {

}
ShakeItController::~ShakeItController() {
}
void ShakeItController::returnToMainMenu() {

}
void ShakeItController::update() {
	MainMenuView menuView;
	MainMenuController menuController(menuView);
	menuController.run();
}
void ShakeItController::run() {
	while (true)
	{
		view.render(model);
		this_thread::sleep_for(std::chrono::milliseconds(500));
	}
}