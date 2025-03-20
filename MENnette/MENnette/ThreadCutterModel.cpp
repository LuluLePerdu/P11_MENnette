#include "ThreadCutterModel.h"
#include <stdlib.h>
#include <iostream>
#include "Color.h"
using namespace std;

ThreadCutterModel::ThreadCutterModel() {
    srand(time(0));
    for (int i = 0; i < 4; i++) {
        LEDarray[i] = rand() % 2;
    }
    LEDscenario();
}

void ThreadCutterModel::LEDscenario() {
    if (LEDarray[0] && LEDarray[1] + LEDarray[2] + LEDarray[3] == 2)
    {
        correctLED = 0;
    }
    else if ((LEDarray[0] && LEDarray[2] && !LEDarray[1] && !LEDarray[3])
            || (LEDarray[0] && LEDarray[1] && LEDarray[2] && LEDarray[3])) {
        correctLED = 2;
    }
    else if (!LEDarray[0] && !LEDarray[1] && !LEDarray[2] && !LEDarray[3]) {
        correctLED = 3;
    }
    else {
        correctLED = 1;
    }
}

bool ThreadCutterModel::getCompleted() {
    return completed;
}

int ThreadCutterModel::getCorrectLED() {
    return correctLED;
}

bool ThreadCutterModel::getLEDstatus(int index) const {
    return LEDarray[index];
}

void ThreadCutterModel::playCutter(int button) {
    if (button == correctLED) {
        completed = true;
    }
}