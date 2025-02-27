#pragma once
#include "MainMenuView.h"
#include "MainMenuController.h"

void returnToMainMenu();

void returnToMainMenu() {
    MainMenuView menuView;
    MainMenuController menuController(menuView);
    menuController.run();
}