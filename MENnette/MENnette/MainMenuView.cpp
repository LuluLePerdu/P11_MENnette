#include "MainMenuView.h"
#include <iostream>

void MainMenuView::render(const MainMenuModel& model) {
    const auto& options = model.getOptions();
    int selectedOption = model.getSelectedOption();

    std::cout << "\033[H\033[J"; 
    std::cout << "Menu Principal\n\n";

    for (int i = 0; i < options.size(); ++i) {
        if (i == selectedOption) {
            std::cout << "> " << options[i] << " <\n";
        }
        else {
            std::cout << options[i] << "\n";
        }
    }
}
