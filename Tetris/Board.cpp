#include "Board.h"

Board::Board() {
    
    grid = std::vector<std::vector<int>>(board_height, std::vector<int>(board_width, 0));
}

bool Board::isFree(int x, int y) const {

    if (x < 0 || x >= board_width) {
        return false;
    }
    if (y < 0 || y >= board_height) {
        return false;
    }
    return grid[y][x] == 0;
}

void Board::placePiece(const Piece& p) {
    for (int i = 0; i < p.getCellCount(); i++) {
        int x = p.getCellX(i);
        int y = p.getCellY(i);
        if (x >= 0 && x < board_width && y >= 0 && y < board_height) {
            grid[y][x] = 1;
        }
    }
}

bool Board::isRowFull(int y) const {
    for (int x = 0; x < board_width; x++) {
        if (grid[y][x] == 0) {
            return false;
        }
    }
    return true;
}

int Board::clearRow(int y) {

    int destroyed = 0;
    for (int x = 0; x < board_width; x++) {
        if (grid[y][x] != 0) {
            destroyed++;
        }
    }

    for (int row = y; row > 0; row--) {
        for (int x = 0; x < board_width; x++) {
            grid[row][x] = grid[row - 1][x];
        }
    }

    for (int x = 0; x < board_width; x++) {
        grid[0][x] = 0;
    }

    return destroyed;
}

int Board::clearFullLines() {
    int removed = 0;
    int y = board_height - 1;
    while (y >= 0) {
        if (isRowFull(y)) {
            clearRow(y);
            removed++;

        }
        else {
            y--;
        }
    }
    return removed;
}

int Board::getCell(int x, int y) const {
    return grid[y][x];
}

void Board::setCell(int x, int y, int value) {
    if (x >= 0 && x < board_width && y >= 0 && y < board_height) {
        grid[y][x] = value;
    }
}

std::string Board::serialize() const {
    std::string data = "";
    for (int y = 0; y < board_height; y++) {
        for (int x = 0; x < board_width; x++) {
            data += (grid[y][x] == 0) ? '0' : '1';
        }
        data += '\n';
    }
    return data;
}

void Board::deserialize(std::istream& in) {
    grid = std::vector<std::vector<int>>(board_height, std::vector<int>(board_width, 0));
    for (int y = 0; y < board_height; y++) {
        std::string line;
        in >> line;
        for (int x = 0; x < board_width && x < (int)line.size(); x++) {
            if (line[x] == '1') {
                grid[y][x] = 1;
            }
        }
    }
}