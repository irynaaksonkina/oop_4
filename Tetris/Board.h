#pragma once
#include <vector>
#include "Piece.h"

const int board_width = 10;
const int board_height = 20;

class Board {
public:
    Board();

    bool isFree(int x, int y) const;
    void placePiece(const Piece& p);
    int clearFullLines();
    int clearRow(int y); 
    int getCell(int x, int y) const;
    void setCell(int x, int y, int value);

private:
    bool isRowFull(int y) const;
    std::vector<std::vector<int>> grid;
};