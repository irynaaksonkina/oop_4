#include "Game.h"


Game::Game(Renderer& r) : renderer(r) {
}

void Game::draw() {
    renderer.render(engine.getBoard(), engine.getPiece(), engine.getScore(), engine.getState());
}


void Game::run() {
    Action choice = renderer.showMenu();
    if (choice == Action::Quit) {
        return;
    }
    engine.handleAction(choice);
    if (engine.getState() != GameState::Playing) {
        engine.handleAction(Action::NewGame);
    }
    draw();

    bool quit = false;
    while (!quit && (engine.getState() == GameState::Playing || engine.getState() == GameState::Paused)) {
        Action a = renderer.pollInput();

        if (a == Action::Quit) {
            quit = true;
        }

        engine.handleAction(a);

        if (a != Action::None) {
            draw();
        }
    }

}