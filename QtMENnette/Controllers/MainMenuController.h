#pragma once

#include "MainMenuModel.h"
#include "MainMenuView.h"

class MainMenuController {
public:
    MainMenuController(MainMenuView& view);

    void run();

private:
    MainMenuModel model;
    MainMenuView& view;
};
