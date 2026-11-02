#pragma once
#include "Piece.h"
#include "Board.h"

class LineCleaner : public Piece {
public:
    LineCleaner();
    int clean(Board& b);
};