#include "LineCleaner.h"

LineCleaner::LineCleaner() : Piece('C') {
    cellCount = 1;
}

int LineCleaner::clean(Board& b) {
    int row = getCellY(0);
    return b.clearRow(row);
}