#pragma once
#include <windows.h>
#include <conio.h>
#include <iostream>
#include <chrono>
#include "SnakeMazeController.h"
#include "MainMenuView.h"
#include "MainMenuController.h"
#include "Communication.h"

SnakeMazeController::SnakeMazeController(SnakeMazeView& v) : view(v) {
    model.initialize();
}

void SnakeMazeController::run() {
    const double frameTime = 1.0 / 60.0;
    double accumulator = 0.0;

    gameClock.start();
    frameClock.start();

    while (model.inGame()) {
        double deltaTime = frameClock.getDeltaTime();
        accumulator += deltaTime;

        if (_kbhit()) {
            char touche = _getch();

            switch (touche) {
            case 'w':
                model.changeDirection(0, -1);
                model.movePlayer();
                break;
            case 's':
                model.changeDirection(0, 1);
                model.movePlayer();
                break;
            case 'a':
                model.changeDirection(-1, 0);
                model.movePlayer();
                break;
            case 'd':
                model.changeDirection(1, 0);
                model.movePlayer();
                break;
            case 27: // Touche �chap
                returnToMainMenu();
                return;
            }
        }

        handleJoystickInput();

        if (accumulator >= frameTime) {
            model.updateTimer();
            accumulator -= frameTime;
        }

        view.render(model);

        std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>((frameTime - deltaTime) * 1000)));
    }

    int timeTaken = static_cast<int>(gameClock.getElapsedTime());
    displayEndGameMessage(model.victoryEOG(), timeTaken);

    returnToMainMenu();

}

void SnakeMazeController::handleJoystickInput() {
    Communication& comm = Communication::getInstance();
	uint8_t joystickValue = comm.readMsg(MSG_ID_AR_JOYSTICK);
	comm.clear();
    if (joystickValue == -1) {
        return; 
    }

    if (joystickValue == 4) {
        model.changeDirection(-1, 0); 
        model.movePlayer();
    }
    else if (joystickValue == 8) {
        model.changeDirection(1, 0);
        model.movePlayer();
    }
    else if (joystickValue == 2) {
        model.changeDirection(0, -1);
        model.movePlayer();
    }
	else if (joystickValue == 1) {
		model.changeDirection(0, 1);
		model.movePlayer();
	}
    else if (joystickValue >= 50 && joystickValue <= 150) {
        model.changeDirection(0, 0); 
    }

}

void SnakeMazeController::displayEndGameMessage(bool victory, int timeTaken) {
    std::cout << "\n\n";
    if (victory) {
        std::cout << "Bravo, vous avez fini le labyrinthe !\n";
    }
    else {
        std::cout << "Dommage, vous avez perdu !\n";
    }
    std::cout << "Temps pris : " << timeTaken << " secondes\n";
    std::cout << "Appuyez sur [Enter] pour retourner au menu principal...\n";

    while (_getch() != '\r');
}

void SnakeMazeController::returnToMainMenu() {
    MainMenuView menuView;
    MainMenuController menuController(menuView);
    menuController.run();
}