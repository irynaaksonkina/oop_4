#pragma once
#include "Piece.h"
#include "Board.h"

class LineCleaner : public Piece {
public:
    LineCleaner();
    void land(Board& b, Score& s) override;
    void rotate() override {}
};