#pragma once
#include "piece.h"

class Board {
private:
    Piece grid[8][8];
    
public:
    Board();
    void initialize();
    Piece getPiece(int row, int col) const;
    void setPiece(int row, int col, const Piece& piece);
    bool movePiece(int startRow, int startCol, int endRow, int endCol);
    void clearSquare(int row, int col);
    };
