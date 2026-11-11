#include "LineCleaner.h"
#include "Board.h"
#include "Score.h"

LineCleaner::LineCleaner() : Piece(PieceType::Cleaner) {
}

void LineCleaner::land(Board& b, Score& s) {
    s.addCleanerPoints(b.clearRow(getCellY(0)));
}