#pragma once
#include <windows.h>
#include <conio.h>
#include <iostream>
#include "SnakeMazeController.h"
#include "MainMenuView.h"
#include "MainMenuController.h"
#include "Communication.h"

SnakeMazeController::SnakeMazeController(SnakeMazeView& v) : view(v) {
    model.initialize();
}

void SnakeMazeController::run()
{
    Communication& comm = Communication::getInstance();
    while (model.inGame()) {

        uint8_t rawInput = comm.readMsg(MSG_ID_AR_JOYSTICK);
        comm.clear();
        if (rawInput != 0) {
            bool input[8] = { 0 };
            comm.byteToBoolArray(rawInput, input);

            switch (rawInput) {
			case 2: //UP
                model.changeDirection(0, -1); 
                break;
			case 1: //DOWN
                model.changeDirection(0, 1); 
                break;
			case 8: //LEFT
                model.changeDirection(-1, 0);  
                break;
			case 4: //RIGHT
                model.changeDirection(1, 0);  
                break;
            case 27:
                return; 
            }
        }

        model.movePlayer();  
        view.render(model);  
        Sleep(100); 
    }
    if (model.victoryEOG()) {
        std::cout << "Félicitations, vous avez gagné !\n";
    }
    else {
        std::cout << "Dommage, vous avez perdu !\n";
        returnToMainMenu();
    }
}

void SnakeMazeController::returnToMainMenu() { 
    MainMenuView menuView;   
    MainMenuController menuController(menuView);
    menuController.run(); 
}

void SnakeMazeController::update()
{
	view.render(model);
}