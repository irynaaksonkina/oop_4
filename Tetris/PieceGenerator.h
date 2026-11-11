#pragma once
#include <memory>
#include "Piece.h"

class PieceGenerator {
public:
    PieceGenerator();

    std::unique_ptr<Piece> createNextPiece();
    void reset();

    std::unique_ptr<Piece> createPiece(PieceType type) const;
    int getCounter() const;
    void setCounter(int value);

private:
    int pieceCounter;
};