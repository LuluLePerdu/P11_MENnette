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
//#include "common.hpp"

using namespace std;

MainMenuController::MainMenuController(MainMenuView& v) : view(v) {
    model = MainMenuModel();
}

void MainMenuController::run() {
    view.render(model);



    Communication& comm = Communication::getInstance();
    while (true) {

        uint8_t rawInput = comm.readMsg(MSG_ID_AR_JOYSTICK);
        comm.clear();
        if (rawInput != 0 && rawInput != -1) {
            /*bool input[8] = { 0 };
            comm.byteToBoolArray(rawInput, input);*/

            if (rawInput == 2) { //UP
                model.selectPreviousOption();
                view.render(model);
            }
            else if (rawInput == 1) { // DOWN
                model.selectNextOption();
                view.render(model);
            }
            else if (rawInput == 8) { // RIGHT/SELECT
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
                    //returnToMainMenu();
                    MainMenuView menuView;
                    MainMenuController menuController(menuView);
                    menuController.run();
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