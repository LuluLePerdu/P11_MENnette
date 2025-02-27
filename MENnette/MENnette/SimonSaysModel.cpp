#include "SimonSaysModel.h"
#include <random>

SimonSaysModel::SimonSaysModel() {
    srand(time(0));
    simonSequence();
}

void SimonSaysModel::simonSequence() {
    for (int i = 0; i < 10; i++) {
        seqArray[i] = rand() % 4;
    }
}

int SimonSaysModel::getElement(int index) const {
    return seqArray[index];
}

bool SimonSaysModel::getCompleted() {
    return completed;
}