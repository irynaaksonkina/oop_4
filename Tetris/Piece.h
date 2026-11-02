#pragma once

class Piece {
public:
    Piece(char type);
    virtual ~Piece() {} 

    void move(int dx, int dy);
    void rotate();

    int getCellX(int i) const;
    int getCellY(int i) const; 
    int getCellCount() const; 
    char getType() const;

protected:
    void setCell(int i, int dx, int dy);
    int x;
    int y;
    char type;
    int cellCount;
    int offsetX[4];
    int offsetY[4];
};