#include "PieceGenerator.h"
#include "LineCleaner.h"
#include <cstdlib>
#include <ctime>

PieceGenerator::PieceGenerator() {
    pieceCounter = 0;
    srand((unsigned)time(0));
}

std::unique_ptr<Piece> PieceGenerator::createNextPiece() {
    pieceCounter++;

    if (pieceCounter % 10 == 0) {
        return std::unique_ptr<Piece>(new LineCleaner());
    }

    const char types[7] = { 'I', 'O', 'T', 'S', 'Z', 'J', 'L' };
    int index = rand() % 7;
    return std::unique_ptr<Piece>(new Piece(types[index]));
}

void PieceGenerator::reset() {
    pieceCounter = 0;
}