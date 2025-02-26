#pragma once
#include "SnakeMazeView.h"
#include "SnakeMazeModel.h"
#include "Color.h"
#include <windows.h>
#include <iostream>

void SnakeMazeView::setColor(int text, int background) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, (background << 4) | text);
}

void SnakeMazeView::render(const SnakeMazeModel& model) {  
    std::cout << "\033[?25l"; 
    std::cout << "\033[H";  

    const char(&maze)[HEIGHT][WIDTH] = model.getMaze();

    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            std::cout << "\033[" << y + 1 << ";" << x + 1 << "H"; 

            if (maze[y][x] == WALL) {
                setColor(BLEU_FONCE, GRIS);  
            }
            else if (maze[y][x] == PLAYER) {
                setColor(JAUNE, NOIR); 
            }
            else if (maze[y][x] == OBJECTIVE) {
                setColor(VERT_CLAIR, NOIR);  
            }
            else {
                setColor(BLANC, NOIR); 
            }

            std::cout << maze[y][x];  
        }
    }

    setColor(BLANC, NOIR);
    std::cout << "\033[?25h";
    std::cout.flush();
}
