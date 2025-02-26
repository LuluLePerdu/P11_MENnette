#include "SimonSaysView.h"
#include <iostream>
using namespace std;

void SimonSaysView::renderElement(const SimonSaysModel& model, int index) {
    cout << model.getElement(index) << " ";
}