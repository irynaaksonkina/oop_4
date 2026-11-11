#pragma once
#include <vector>
#include "Piece.h"
#include <string>
#include <istream>


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
    std::string serialize() const;
    void deserialize(std::istream& in);

private:
    bool isRowFull(int y) const;
    std::vector<std::vector<int>> grid;
};