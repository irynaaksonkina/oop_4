#include "Piece.h"

Piece::Piece(char type) {
    this->type = type;
    x = 4;
    y = 0;
    cellCount = 4;

    setCell(0, 0, 0);

    if (type == 'I') {
        setCell(1, -1, 0);
        setCell(2, 1, 0);
        setCell(3, 2, 0);
    }
    else if (type == 'O') {
        setCell(1, 1, 0);
        setCell(2, 0, 1);
        setCell(3, 1, 1);
    }
    else if (type == 'T') {
        setCell(1, -1, 0);
        setCell(2, 1, 0);
        setCell(3, 0, 1);
    }
    else if (type == 'S') {
        setCell(1, 1, 0);
        setCell(2, -1, 1);
        setCell(3, 0, 1);
    }
    else if (type == 'Z') {
        setCell(1, -1, 0);
        setCell(2, 0, 1);
        setCell(3, 1, 1);
    }
    else if (type == 'J') {
        setCell(1, -1, 0);
        setCell(2, 1, 0);
        setCell(3, 1, 1);
    }
    else if (type == 'L') {
        setCell(1, -1, 0);
        setCell(2, 1, 0);
        setCell(3, -1, 1);
    }
}

void Piece::move(int dx, int dy) {
    x = x + dx;
    y = y + dy;
}

void Piece::rotate() {
   
    if (type == 'O') {
        return;
    }

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

char Piece::getType() const {
    return type;
}