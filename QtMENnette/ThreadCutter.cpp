#include "ThreadCutter.h"
#include <iostream>
using namespace std;

ThreadCutter::ThreadCutter() {
    srand(time(0));
    for (int i = 0; i < 4; i++) {
        ledArray[i] = rand() % 2;
    }
    ledSetup();
    render();
}

void ThreadCutter::run() {
    bool ledArray[8];
    Communication& comm = Communication::getInstance();

    int msgInput;
    comm.clear();

    do
    {
        msgInput = comm.readMsg(MSG_ID_AR_BUTTON);
        comm.clear();
        if (msgInput == -2) {
            return;
        }
    } while (msgInput == -1);

    switch (msgInput)
    {
    case 1:
        checkButton(3);
        break;
    case 2:
        checkButton(2);
        break;
    case 4:
        checkButton(1);
        break;
    case 8:
        checkButton(0);
        break;
    default:
        break;
    }
}

bool ThreadCutter::checkButton(int button) {
    if (button == correctLed) completed = true;
	return completed;
}

void ThreadCutter::render() {
    /*
    labInstruc->setText(QString::fromLatin1(
        "Si la DEL verte et 2 autres DELs sont allumées, appuyez sur le bouton vert."
        "\n\nSinon, si la DEL verte et la DEL rouge sont allumées mais aucune autre, appuyez sur le bouton rouge."
        "\n\nSinon, si les 4 DELs sont allumées, appuyez sur le bouton rouge."
        "\n\nSinon, si les 4 DELs sont éteintes, appuyez sur le bouton la plus à droite."
        "\n\nSinon, si la DEL bleue et la DEL jaune sont allumées mais aucune autre, appuyez sur le bouton jaune."
        "\n\nSinon, si uniquement la DEL rouge est allumée, appuyez sur le bouton le plus à gauche."
        "\n\nSinon, si aucune des autres conditions n'est remplie mais que 2 DELs sont allumées, appuyez sur le bouton rouge."
        "\n\nSinon, appuyez sur le deuxième bouton à partir de la gauche."));
    */
}

bool ThreadCutter::getCompleted() {
    return completed;
}

void ThreadCutter::ledSetup() {
    /* old code (fonctionne mais moins complet et clair)
    if (ledArray[0] && ledArray[1] + ledArray[2] + ledArray[3] == 2)
    {
        correctLed = 1;
    }
    else if ((ledArray[0] && ledArray[2] && !ledArray[1] && !ledArray[3])
        || (ledArray[0] && ledArray[1] && ledArray[2] && ledArray[3])) {
        correctLed = 3;
    }
    else if (!ledArray[0] && !ledArray[1] && !ledArray[2] && !ledArray[3]) {
        correctLed = 4;
    }
    else {
        correctLed = 2;
    }
    */
    if ((ledArray[GREEN] && ledArray[BLUE] + ledArray[RED] + ledArray[YELLOW] == 2)
        || (!ledArray[GREEN] && !ledArray[BLUE] && ledArray[RED] && !ledArray[YELLOW]))
    {
        correctLed = GREEN;
    }
    else if ((ledArray[GREEN] && ledArray[RED] && !ledArray[BLUE] && !ledArray[YELLOW])
        || (ledArray[GREEN] && ledArray[BLUE] && ledArray[RED] && ledArray[YELLOW])) {
        correctLed = RED;
    }
    else if ((!ledArray[GREEN] && !ledArray[BLUE] && !ledArray[RED] && !ledArray[YELLOW])
        || (ledArray[BLUE] && ledArray[YELLOW] && !ledArray[GREEN] && !ledArray[RED])) {
        correctLed = YELLOW;
    }
    else if (ledArray[GREEN] + ledArray[BLUE] + ledArray[RED] + ledArray[YELLOW] == 2) {
        correctLed = RED;
    }
    else {
        correctLed = BLUE;
    }
}