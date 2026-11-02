#include <SFML/Graphics.hpp>
#include "Game.h"
#include "SFMLRenderer.h"
// #include "ConsoleRenderer.h"

int main() {
    SFMLRenderer renderer;
    // ConsoleRenderer renderer;
    Game game(renderer);
    game.run();
    return 0;
}
