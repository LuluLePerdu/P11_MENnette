#include "ShakeItView.h"
#include "ShakeItModel.h"
#include <iostream>
#include <string>
#include <iomanip>

#define RESET   "\033[0m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define RED     "\033[31m"

using namespace std;

void ShakeItView::render(ShakeItModel& model)
{
    int length = model.getLength();
    int maxLength = model.getMaxLength();
    int maxValue = model.getMaxValue();

    cout << "\033[?25l"; //flicker resolver
    cout << "\033[H";

    for (int i = 0; i < maxLength + 2; i++) {
        cout << "-";
    }
    cout << "\n|";

    for (int i = 0; i < maxLength; i++) {
        if (i <= length) {
            if (i < maxLength * 0.35) {
                cout << GREEN << "#" << RESET;
            }
            else if (i < maxLength * 0.7) {
                cout << YELLOW << "#" << RESET;
            }
            else {
                cout << RED << "#" << RESET;
            }
        }
        else {
            cout << " ";
        }
    }

    cout << "|\n";
    for (int i = 0; i < maxLength + 2; i++) {
        cout << "-";
    }

    cout << endl;
    cout << "Value: " << setw(5) << right << model.realValue << " / 1023" << endl;
}