#pragma once
#include <windows.h>
#include <conio.h>
#include <iostream>
#include "SnakeMazeController.h"
#include "MainMenuView.h"
#include "MainMenuController.h"

SnakeMazeController::SnakeMazeController(SnakeMazeView& v) : view(v) {
    model.initialize();
}

void SnakeMazeController::run()
{
    while (model.inGame()) {
        if (_kbhit()) {
            char touche = _getch(); 

            switch (touche) {
            case 'w':
                model.changeDirection(0, -1); 
                break;
            case 's':
                model.changeDirection(0, 1); 
                break;
            case 'a':
                model.changeDirection(-1, 0);  
                break;
            case 'd':
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