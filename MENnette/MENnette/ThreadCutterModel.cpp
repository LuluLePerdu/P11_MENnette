#include "ThreadCutterModel.h"
#include <stdlib.h>
#include <iostream>
#include "Color.h"
using namespace std;

ThreadCutterModel::ThreadCutterModel() {
    for (int i = 0; i < 4; i++) {
        LEDarray[i] = rand() % 2;
    }
    LEDscenario();
}

void ThreadCutterModel::LEDscenario() {
    if (LEDarray[0] && LEDarray[1] + LEDarray[2] + LEDarray[3] == 2)
    {
        correctLED = 1;
    }
    else if ((LEDarray[0] && LEDarray[2] && !LEDarray[1] && !LEDarray[3])
            || (LEDarray[0] && LEDarray[1] && LEDarray[2] && LEDarray[3])) {
        correctLED = 3;
    }
    else if (!LEDarray[0] && !LEDarray[1] && !LEDarray[2] && !LEDarray[3]) {
        correctLED = 4;
    }
    else {
        correctLED = 2;
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