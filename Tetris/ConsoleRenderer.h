#pragma once
#include <ctime>
#include "Renderer.h"


class ConsoleRenderer : public Renderer {
public:
    ConsoleRenderer();
    Action pollInput() override;
    Action showMenu() override;
    void render(const Board& board, const Piece& piece,
        const Score& score, GameState state) override;

private:
    float fallInterval;
    clock_t lastTick;
};