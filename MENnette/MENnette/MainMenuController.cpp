#pragma once
#include "MainMenuController.h"
#include "SnakeMazeController.h"
#include "ShakeItController.h"
#include "SimonSaysController.h"
#include "ThreadCutterController.h"
#include <conio.h>
#include <iostream>
#include <chrono>
#include <thread>
#include "Communication.h"
#include "PotentiometreAll.h"

using namespace std;

MainMenuController::MainMenuController(MainMenuView& v) : view(v) {
	model = MainMenuModel();
}

void MainMenuController::run() {
    view.render(model);
    
    

    while (true) {

        //int msg = comm.readMsg(MSG_ID_POTENTIOMETER);
		//comm.clear();
        if (_kbhit()) {
            char key = _getch();


            if (key == 'w') {
                model.selectPreviousOption();
                view.render(model);
            }
            else if (key == 's') {
                model.selectNextOption();
                view.render(model);
            }
            else if (key == '\r') {
                if (model.getSelectedOption() == 0) {
                    startSnakeGame();
                }
                if (model.getSelectedOption() == 2) {
                    return;
                }
                if (model.getSelectedOption() == 3) {
                    ShakeItView shakeItView;
                    ShakeItController shakeItController(shakeItView);
                    shakeItController.run();
                }
                if (model.getSelectedOption() == 4) {
                    ThreadCutterView threadView;
                    ThreadCutterController threadController(threadView);
                    threadController.run();
                }
                if (model.getSelectedOption() == 5) {
                    SimonSaysView simonView;
                    SimonSaysController simonController(simonView);
                    simonController.run();
                }
				if (model.getSelectedOption() == 6) {
					playPot();
					return;
				}
                break;
            }
        }
        this_thread::sleep_for(std::chrono::milliseconds(33));
    }
}

void MainMenuController::startSnakeGame() {
    SnakeMazeView snakeView;
    SnakeMazeController snakeController(snakeView);

    snakeController.run();
}