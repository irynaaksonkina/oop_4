#include "GameEngine.h"
#include "LineCleaner.h"
#include <string>
#include <sstream>

GameEngine::GameEngine() {
    state = GameState::Menu;
    landed = false;
    
    currentPiece = generator.createNextPiece();
}

void GameEngine::startNewGame() {
    board = Board();
    score.reset();
    score.setBest(storage.loadBestScore()); 
    generator.reset();
    currentPiece = generator.createNextPiece();
    landed = false;
    state = GameState::Playing;
}

bool GameEngine::canMove(int dx, int dy) const {
    for (int i = 0; i < currentPiece->getCellCount(); i++) {
        int newX = currentPiece->getCellX(i) + dx;
        int newY = currentPiece->getCellY(i) + dy;
        if (!board.isFree(newX, newY)) {
            return false;
        }
    }
    return true;
}

void GameEngine::tryRotate() {
    currentPiece->rotate();
    if (!canMove(0, 0)) {
        currentPiece->rotate();
        currentPiece->rotate();
        currentPiece->rotate();
    }
}

void GameEngine::tick() {
    if (canMove(0, 1)) {
        currentPiece->move(0, 1);
        landed = false;
    }
    else if (!landed) {
        landed = true;
    }
    else {
        lockPiece();
    }
}

void GameEngine::lockPiece() {
    LineCleaner* cleaner = dynamic_cast<LineCleaner*>(currentPiece.get());

    if (cleaner != nullptr) {
        int destroyed = cleaner->clean(board);
        score.addCleanerPoints(destroyed);
    }
    else {
        board.placePiece(*currentPiece);
        int lines = board.clearFullLines();
        score.addLines(lines);
    }

    if (score.isVictory()) {
        finishGame(GameState::Victory);
        return;
    }

    currentPiece = generator.createNextPiece();
    landed = false;
    if (!canMove(0, 0)) {
        finishGame(GameState::GameOver);
    }
}

void GameEngine::finishGame(GameState newState) {
    state = newState;
    if (score.getCurrent() > score.getBest()) {
        score.setBest(score.getCurrent());
        storage.saveBestScore(score.getCurrent());
    }
}

void GameEngine::togglePause() {
    if (state == GameState::Playing) {
        state = GameState::Paused;
    }
    else if (state == GameState::Paused) {
        state = GameState::Playing;
    }
}

void GameEngine::saveGame() {
    std::string data = "";
    for (int y = 0; y < board_height; y++) {
        for (int x = 0; x < board_width; x++) {
            if (board.getCell(x, y) == 0) {
                data = data + "0";
            }
            else {
                data = data + "1";
            }
        }
        data = data + "\n";
    }
    data = data + std::to_string(score.getCurrent()) + "\n";
    storage.saveGame(data);
}

void GameEngine::loadGame() {
    std::string data = storage.loadGame();
    if (data == "") {
        return;
    }

    std::istringstream in(data);
    board = Board();
    for (int y = 0; y < board_height; y++) {
        std::string line;
        in >> line;
        for (int x = 0; x < board_width && x < (int)line.size(); x++) {
            if (line[x] == '1') {
                board.setCell(x, y, 1);
            }
        }
    }

    int savedScore = 0;
    in >> savedScore;
    score.setCurrent(savedScore);
    score.setBest(storage.loadBestScore());

    generator.reset();
    currentPiece = generator.createNextPiece();
    landed = false;
    state = GameState::Playing;
}

void GameEngine::handleAction(Action a) {
    if (a == Action::NewGame) {
        startNewGame();
        return;
    }
    if (a == Action::LoadGame) {
        loadGame();
        return;
    }
    if (a == Action::Pause) {
        togglePause();
        return;
    }
    if (a == Action::Save) {
        if (state == GameState::Playing || state == GameState::Paused) {
            saveGame();
        }
        return;
    }

    if (state != GameState::Playing) {
        return;
    }

    if (a == Action::MoveLeft) {
        if (canMove(-1, 0)) {
            currentPiece->move(-1, 0);
        }
    }
    else if (a == Action::MoveRight) {
        if (canMove(1, 0)) {
            currentPiece->move(1, 0);
        }
    }
    else if (a == Action::Rotate) {
        tryRotate();
    }
    else if (a == Action::Tick) {
        tick();
    }
}

const Board& GameEngine::getBoard() const {
    return board;
}

const Piece& GameEngine::getPiece() const {
    return *currentPiece;
}

const Score& GameEngine::getScore() const {
    return score;
}

GameState GameEngine::getState() const {
    return state;
}