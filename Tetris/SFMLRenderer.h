#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include "Renderer.h"

class SFMLRenderer : public Renderer {
public:
    SFMLRenderer();
    Action pollInput() override;
    Action showMenu() override;
    void render(const Board& board, const Piece& piece,
        const Score& score, GameState state) override;

private:
    void drawCell(int x, int y, sf::Color color);
    void drawText(const std::string& str, float x, float y, int size);
    sf::Color getPieceColor(char type) const;
    void drawBox(float x, float y, float w, float h, sf::Color fill);
    void waitForEnter();

    sf::RenderWindow window;
    sf::Font font;
    sf::Clock fallClock;
    float fallInterval;
    int cellSize;
    int boardX;
    int boardY;
};
