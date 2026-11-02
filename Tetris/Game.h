#pragma once
#include "GameEngine.h"
#include "Renderer.h"

class Game {
public:
    Game(Renderer& r);
    void run();

private:
    void draw();

    GameEngine engine;
    Renderer& renderer;
};
