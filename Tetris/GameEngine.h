#pragma once
#include <memory>
#include "Types.h"
#include "Board.h"
#include "Score.h"
#include "Piece.h"
#include "PieceGenerator.h"
#include "Storage.h"

class GameEngine {
public:
    GameEngine();

    void startNewGame();
    void handleAction(Action a);

    const Board& getBoard() const;
    const Piece& getPiece() const;
    const Score& getScore() const;
    GameState getState() const;

private:
    Board board;
    Score score;
    std::unique_ptr<Piece> currentPiece;
    GameState state;
    bool landed;
    PieceGenerator generator;
    Storage storage;

    bool canMove(int dx, int dy) const; 
    void tryRotate();
    void tick();
    void lockPiece();
    void finishGame(GameState newState);

    void togglePause();
    void saveGame();
    void loadGame();
};
