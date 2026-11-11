#pragma once

enum class PieceType { I, O, T, S, Z, J, L, Cleaner };
class Board;
class Score; 

class Piece {
public:
    explicit Piece(PieceType type);
    virtual ~Piece() {} 

    void move(int dx, int dy);
    virtual void rotate();
    virtual void land(Board& b, Score& s);

    int getCellX(int i) const;
    int getCellY(int i) const; 
    int getCellCount() const; 
    PieceType getType() const;
    int getX() const;
    int getY() const;
    int getRotation() const;
    void restore(int newX, int newY, int newRotation);

protected:
    void setCell(int i, int dx, int dy);
    int x;
    int y;
    PieceType type;
    int cellCount;
    int offsetX[4];
    int offsetY[4];
    int rotation;
};

class OPiece : public Piece {
public:
    OPiece() : Piece(PieceType::O) {}
    void rotate() override {}
};