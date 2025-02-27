#include "MainMenuModel.h"

MainMenuModel::MainMenuModel() : selectedOption(0) {
    options = { "Jouer", "Options", "Quitter", "test", "DEL", "Simon"};
}

const std::vector<std::string>& MainMenuModel::getOptions() const {
    return options;
}

int MainMenuModel::getSelectedOption() const {
    return selectedOption;
}

void MainMenuModel::selectNextOption() {
    selectedOption = (selectedOption + 1) % options.size();
}

void MainMenuModel::selectPreviousOption() {
    selectedOption = (selectedOption - 1 + options.size()) % options.size();
}

void MainMenuModel::confirmSelection() {

}
