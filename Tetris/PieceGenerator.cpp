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
        return createPiece(PieceType::Cleaner);
    }

    const PieceType types[7] = { PieceType::I, PieceType::O, PieceType::T, PieceType::S,
                                 PieceType::Z, PieceType::J, PieceType::L };
    int index = rand() % 7;
    return createPiece(types[index]);
}

std::unique_ptr<Piece> PieceGenerator::createPiece(PieceType type) const {
    if (type == PieceType::O) {
        return std::unique_ptr<Piece>(new OPiece());
    }
    if (type == PieceType::Cleaner) {
        return std::unique_ptr<Piece>(new LineCleaner());
    }
    return std::unique_ptr<Piece>(new Piece(type));
}

int PieceGenerator::getCounter() const { return pieceCounter; }
void PieceGenerator::setCounter(int value) { pieceCounter = value; }

void PieceGenerator::reset() {
    pieceCounter = 0;
}