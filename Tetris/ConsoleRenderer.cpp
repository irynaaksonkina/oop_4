#include "ConsoleRenderer.h"
#include <iostream>
#include <ctime>
#include <conio.h>
#include <cctype>
#include <cstdlib>


ConsoleRenderer::ConsoleRenderer() {
    fallInterval = 0.5f;
    lastTick = clock();
}


Action ConsoleRenderer::showMenu() {
    std::cout << "TETRIS" << std::endl;
    std::cout << "1 - New Game" << std::endl;
    std::cout << "2 - Load Game" << std::endl;
    std::cout << "Q - Quit" << std::endl;

    while (true) {
        char key = _getch();
        if (key == '1') {
            return Action::NewGame;
        }
        else if (key == '2') {
            return Action::LoadGame;
        }
        else if (key == 'q' || key == 'Q') {
            return Action::Quit;
        }
    }
}

Action ConsoleRenderer::pollInput() {

    if (_kbhit()) {
        char key = _getch();
        key = tolower(key);

        if (key == 'a') {
            return Action::MoveLeft;
        }
        else if (key == 'd') {
            return Action::MoveRight;
        }
        else if (key == 'w') {
            return Action::Rotate;
        }
        else if (key == 's') {
            return Action::Tick;
        }
        else if (key == 'p') {
            return Action::Pause;
        }
        else if (key == 'v') {
            return Action::Save;
        }
        else if (key == 'q') {
            return Action::Quit;
        }
    }

    float passed = (float)(clock() - lastTick) / CLOCKS_PER_SEC;

    if (passed >= fallInterval) {
        lastTick = clock();
        return Action::Tick;
    }
    return Action::None;
}


void ConsoleRenderer::render(const Board& board, const Piece& piece, const Score& score, GameState state) {
    system("cls");
    for (int y = 0; y < board_height; y++) {
        for (int x = 0; x < board_width; x++) {

            bool isPiece = false;
            for (int i = 0; i < piece.getCellCount(); i++) {
                if (piece.getCellX(i) == x && piece.getCellY(i) == y) {
                    isPiece = true;
                }
            }

            if (isPiece) {
                std::cout << "@";
            }
            else if (board.getCell(x, y) == 1) {
                std::cout << "#";
            }
            else {
                std::cout << ".";
            }
        }
        std::cout << std::endl;
    }

    std::cout << "Score: " << score.getCurrent() << "  Best: " << score.getBest() << std::endl;

    if (state == GameState::Menu) {
        std::cout << "Menu" << std::endl;
    }
    else if (state == GameState::Playing) {
        std::cout << "Playing" << std::endl;
    }
    else if (state == GameState::Paused) {
        std::cout << "Paused" << std::endl;
    }
    else if (state == GameState::GameOver) {
        std::cout << "GAME OVER" << std::endl;
    }
    else if (state == GameState::Victory) {
        std::cout << "VICTORY" << std::endl;
    }
}

