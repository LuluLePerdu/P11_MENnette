#include "ThreadCutter.h"
#include <iostream>
using namespace std;

ThreadCutter::ThreadCutter(QLabel* labInstruction, QLabel* labResults) {
    srand(time(0));
    for (int i = 0; i < 4; i++) {
        ledArray[i] = rand() % 2;
    }
    ledSetup();
    labResult->setVisible(false);
}

void ThreadCutter::run(int button) {
    bool ledArray[8];
    Communication& comm = Communication::getInstance();

    int msgInput;
    comm.clear();

    do
    {
        msgInput = comm.readMsg(MSG_ID_AR_BUTTON);
        comm.clear();
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

    if (completed) {
        //cout << endl << "Module desamorce." << endl;
        labResult->setText("Module désamorcé");
        labResult->setVisible(true);
    }
    else {
        //cout << endl << "Mauvais bouton!" << endl;
        labResult->setText("Mauvais bouton!");
        labResult->setVisible(true);
    }
}

bool ThreadCutter::checkButton(int button) {
    if (button == correctLed) completed = true;
}

void ThreadCutter::render() {
    labInstruc->setText(QString::fromLatin1("Si la DEL rouge et 2 autres DELs sont allumées, appuyez sur le bouton rouge."
        "\n\nSinon, si la DEL rouge et la DEL bleue sont allumées mais aucune autre, appuyez sur le bouton bleu pendant 3 secondes."
        "\n\nSinon, si les 4 DELs sont allumées, appuyez sur le bouton bleu."
        "\n\nSinon, si les 4 DELs sont éteintes, appuyez sur le bouton la plus à droite."
        "\n\nSinon, appuyez sur le deuxième bouton à partir de la gauche."));
}

bool ThreadCutter::getCompleted() {
    return completed;
}

void ThreadCutter::ledSetup() {
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
}