#pragma once
#include "SnakeMazeView.h"
#include "SnakeMazeModel.h"
#include "Color.h"
#include <windows.h>
#include <iostream>
#include <iomanip>

void SnakeMazeView::setColor(int text, int background) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, (background << 4) | text);
}

void SnakeMazeView::render(const SnakeMazeModel& model) {
    std::cout << "\033[?25l"; 
    std::cout << "\033[H"; 

    const char(&maze)[HEIGHT][WIDTH] = model.getMaze();

    int timeLeft = model.getTimeLeft();
    int score = model.getScore();

    std::cout << "\033[1;1H";
    setColor(BLANC, NOIR);
    std::cout << "Temps restant: ";

    if (timeLeft >= 0) {
        setColor(VERT_CLAIR, NOIR); 
    }
    else {
        setColor(ROUGE, NOIR); 
    }
    std::cout << std::setw(3) << timeLeft << "s";

    setColor(BLANC, NOIR);
    std::cout << "   Score: " << score << "\n\n";

    // Afficher le labyrinthe
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            std::cout << "\033[" << y + 3 << ";" << x + 1 << "H"; 

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