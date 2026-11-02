#pragma once
#include <memory>
#include "Piece.h"

class PieceGenerator {
public:
    PieceGenerator();

    std::unique_ptr<Piece> createNextPiece();
    void reset();

private:
    int pieceCounter;
};