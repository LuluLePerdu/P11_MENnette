#include "ShakeItView.h"
#include "ShakeItModel.h"

void ShakeItView::render(ShakeItModel& model)
{
	int length = model.getLength();
	int maxLength = model.getMaxLength();
	int maxValue = model.getMaxValue();

	system("cls");
    for (int i = 0; i < maxLength + 2; i++) {
        cout << "-";
    }
	cout << endl << "|";
    for (int i = 0; i < maxLength; i++) {
        if (i < length && i < maxLength * 0.3) {
            cout << GREEN << "#" << RESET;
        }
        else if (i < length && i < maxLength * 0.7) {
            cout << YELLOW << "#" << RESET;
        }
        else if (i < length && i < maxLength) {
            cout << RED << "#" << RESET;
        }
        else { cout << " "; }
    }
	cout << "|" << endl;
    for (int i = 0; i < maxLength + 2; i++) {
        cout << "-";
    }
	cout << endl;
}