#pragma once
#include "Types.h"
#include "Board.h"
#include "Piece.h"
#include "Score.h"

class Renderer {
public:
    virtual ~Renderer() {}

    virtual Action pollInput() = 0;
    virtual Action showMenu() = 0;
    virtual void render(const Board& board, const Piece& piece,
        const Score& score, GameState state) = 0;
};