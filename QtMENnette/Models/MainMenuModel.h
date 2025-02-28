#pragma once

#include <vector>
#include <string>

class MainMenuModel {
public:
    MainMenuModel();
    const std::vector<std::string>& getOptions() const;
    int getSelectedOption() const;
    void selectNextOption();
    void selectPreviousOption();
    void confirmSelection();

private:
    std::vector<std::string> options; 
    int selectedOption;              

};
