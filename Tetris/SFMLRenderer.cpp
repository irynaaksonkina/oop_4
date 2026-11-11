#include "SFMLRenderer.h"
#include <optional>

SFMLRenderer::SFMLRenderer()
    : window(sf::VideoMode({ 520, 640 }), "Tetris")
{
    window.setFramerateLimit(60);
    (void)font.openFromFile("C:/Windows/Fonts/arial.ttf");
    fallInterval = 0.5f;
    cellSize = 30;
    boardX = 20;
    boardY = 20;
}

sf::Color SFMLRenderer::getPieceColor(PieceType type) const {
    if (type == PieceType::I) return sf::Color(0, 200, 220);
    if (type == PieceType::O) return sf::Color(240, 220, 0);
    if (type == PieceType::T) return sf::Color(160, 60, 200);
    if (type == PieceType::S) return sf::Color(60, 200, 60);
    if (type == PieceType::Z) return sf::Color(220, 50, 50);
    if (type == PieceType::J) return sf::Color(50, 80, 220);
    if (type == PieceType::L) return sf::Color(240, 140, 0);
    return sf::Color::White;
}

void SFMLRenderer::drawCell(int x, int y, sf::Color color) {
    float size = (float)(cellSize - 2);
    float px = (float)(boardX + x * cellSize + 1);
    float py = (float)(boardY + y * cellSize + 1);

    sf::RectangleShape rect(sf::Vector2f(size, size));
    rect.setPosition(sf::Vector2f(px, py));
    rect.setFillColor(color);
    rect.setOutlineThickness(-3);
    rect.setOutlineColor(sf::Color(255, 255, 255, 60));
    window.draw(rect);
}

void SFMLRenderer::drawBox(float x, float y, float w, float h, sf::Color fill) {
    sf::RectangleShape box(sf::Vector2f(w, h));
    box.setPosition(sf::Vector2f(x, y));
    box.setFillColor(fill);
    box.setOutlineThickness(2);
    box.setOutlineColor(sf::Color(120, 120, 160));
    window.draw(box);
}

void SFMLRenderer::waitForEnter() {
    while (window.isOpen()) {
        while (const std::optional<sf::Event> event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
            if (const auto* key = event->getIf<sf::Event::KeyPressed>()) {
                if (key->code == sf::Keyboard::Key::Enter) {
                    return;
                }
            }
        }
        sf::sleep(sf::milliseconds(20));
    }
}

void SFMLRenderer::drawText(const std::string& str, float x, float y, int size) {
    sf::Text text(font, str, size);
    text.setPosition(sf::Vector2f(x, y));
    text.setFillColor(sf::Color::White);
    window.draw(text);
}

Action SFMLRenderer::showMenu() {
    while (window.isOpen()) {
        while (const std::optional<sf::Event> event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
                return Action::Quit;
            }
            if (const auto* key = event->getIf<sf::Event::KeyPressed>()) {
                if (key->code == sf::Keyboard::Key::Num1) return Action::NewGame;
                if (key->code == sf::Keyboard::Key::Num2) return Action::LoadGame;
                if (key->code == sf::Keyboard::Key::Q) return Action::Quit;
            }
        }

        window.clear(sf::Color(20, 20, 30));
        drawText("TETRIS", 150, 150, 60);
        drawText("1 - New Game", 150, 280, 30);
        drawText("2 - Load Game", 150, 330, 30);
        drawText("Q - Quit", 150, 380, 30);
        window.display();
    }
    return Action::Quit;
}

Action SFMLRenderer::pollInput() {
    while (const std::optional<sf::Event> event = window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            window.close();
            return Action::Quit;
        }
        if (const auto* key = event->getIf<sf::Event::KeyPressed>()) {
            if (key->code == sf::Keyboard::Key::A || key->code == sf::Keyboard::Key::Left)
                return Action::MoveLeft;
            if (key->code == sf::Keyboard::Key::D || key->code == sf::Keyboard::Key::Right)
                return Action::MoveRight;
            if (key->code == sf::Keyboard::Key::W || key->code == sf::Keyboard::Key::Up)
                return Action::Rotate;
            if (key->code == sf::Keyboard::Key::S || key->code == sf::Keyboard::Key::Down)
                return Action::Tick;
            if (key->code == sf::Keyboard::Key::P) return Action::Pause;
            if (key->code == sf::Keyboard::Key::V) return Action::Save;
            if (key->code == sf::Keyboard::Key::Q || key->code == sf::Keyboard::Key::Escape)
                return Action::Quit;
        }
    }

    if (fallClock.getElapsedTime().asSeconds() >= fallInterval) {
        fallClock.restart();
        return Action::Tick;
    }

}

void SFMLRenderer::render(const Board& board, const Piece& piece,
    const Score& score, GameState state) {
    if (!window.isOpen()) {
        return;
    }

    window.clear(sf::Color(15, 15, 25));

    //рамка поля
    drawBox((float)(boardX - 4), (float)(boardY - 4), 308, 608, sf::Color(25, 25, 40));

    //поле
    for (int y = 0; y < board_height; y++) {
        for (int x = 0; x < board_width; x++) {
            sf::Color color(30, 30, 45);
            if (board.getCell(x, y) == 1) {
                color = sf::Color(90, 130, 200);
            }
            drawCell(x, y, color);
        }
    }

    //фігура, що падає
    for (int i = 0; i < piece.getCellCount(); i++) {
        int x = piece.getCellX(i);
        int y = piece.getCellY(i);
        if (y >= 0) {
            drawCell(x, y, getPieceColor(piece.getType()));
        }
    }

    //панель з рахунком
    drawBox(340, 16, 160, 150, sf::Color(25, 25, 40));
    drawText("SCORE", 355, 28, 18);
    drawText(std::to_string(score.getCurrent()), 355, 50, 32);
    drawText("BEST", 355, 95, 18);
    drawText(std::to_string(score.getBest()), 355, 117, 32);

    //панель з керуванням
    drawBox(340, 380, 160, 240, sf::Color(25, 25, 40));
    drawText("CONTROLS", 355, 392, 20);
    drawText("A/D - move\nW - rotate\nS - down\nP - pause\nV - save\nQ - quit", 355, 430, 18);

    //затемнення і напис
    if (state == GameState::Paused || state == GameState::GameOver || state == GameState::Victory) {
        sf::RectangleShape dark(sf::Vector2f(300, 600));
        dark.setPosition(sf::Vector2f((float)boardX, (float)boardY));
        dark.setFillColor(sf::Color(0, 0, 0, 170));
        window.draw(dark);

        if (state == GameState::Paused) {
            drawText("PAUSED", 85, 270, 40);
        }
        else if (state == GameState::GameOver) {
            drawText("GAME OVER", 50, 270, 40);
            drawText("Press Enter", 85, 330, 22);
        }
        else {
            drawText("VICTORY", 65, 270, 40);
            drawText("Press Enter", 85, 330, 22);
        }
    }

    window.display();

    if (state == GameState::GameOver || state == GameState::Victory) {
        waitForEnter();
    }
}