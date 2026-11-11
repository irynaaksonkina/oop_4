#include "Piece.h"
#include "Board.h"
#include "Score.h"

Piece::Piece(PieceType type) {
    this->type = type;
    x = 4;
    y = 1;
    rotation = 0;
    cellCount = 4;

    for (int i = 0; i < 4; i++) {
        setCell(i, 0, 0);
    }

    switch (type) {
    case PieceType::I:
        setCell(1, -1, 0); setCell(2, 1, 0); setCell(3, 2, 0);
        break;
    case PieceType::O:
        setCell(1, 1, 0); setCell(2, 0, 1); setCell(3, 1, 1);
        break;
    case PieceType::T:
        setCell(1, -1, 0); setCell(2, 1, 0); setCell(3, 0, 1);
        break;
    case PieceType::S:
        setCell(1, 1, 0); setCell(2, -1, 1); setCell(3, 0, 1);
        break;
    case PieceType::Z:
        setCell(1, -1, 0); setCell(2, 0, 1); setCell(3, 1, 1);
        break;
    case PieceType::J:
        setCell(1, -1, 0); setCell(2, 1, 0); setCell(3, 1, 1);
        break;
    case PieceType::L:
        setCell(1, -1, 0); setCell(2, 1, 0); setCell(3, -1, 1);
        break;
    case PieceType::Cleaner:
        cellCount = 1;
        break;
    }
}

void Piece::move(int dx, int dy) {
    x = x + dx;
    y = y + dy;
}

void Piece::rotate() {
   
    rotation = (rotation + 1) % 4;

    for (int i = 0; i < cellCount; i++) {
        int oldX = offsetX[i];
        int oldY = offsetY[i];
        offsetX[i] = -oldY;
        offsetY[i] = oldX;
    }
}

void Piece::setCell(int i, int dx, int dy) {
    offsetX[i] = dx;
    offsetY[i] = dy;
}

int Piece::getCellX(int i) const {
    return x + offsetX[i];
}

int Piece::getCellY(int i) const {
    return y + offsetY[i];
}

int Piece::getCellCount() const {
    return cellCount;
}

PieceType Piece::getType() const {
    return type;
}

int Piece::getX() const { return x; }
int Piece::getY() const { return y; }
int Piece::getRotation() const { return rotation; }

void Piece::restore(int newX, int newY, int newRotation) {
    x = newX;
    y = newY;
    for (int i = 0; i < newRotation % 4; i++) {
        rotate();
    }
}

void Piece::land(Board& b, Score& s) {
    b.placePiece(*this);
    s.addLines(b.clearFullLines());
}