#pragma once
#include "piece.h"
#include <cmath>
class Board {
private:
    Piece grid[8][8];
    
    //en passant
    int enPassantCol;
    
    //castling
    bool whiteKingMoved;
    bool whiteKRookMoved;
    bool whiteQRookMoved;
    
    bool blackKingMoved;
    bool blackKRookMoved;
    bool blackQRookMoved;
    
public:
    Board();
    Board(const Board& other);
    void initialize();
    Piece getPiece(int row, int col) const;
    void setPiece(int row, int col, const Piece& piece);
    bool movePiece(int startRow, int startCol, int endRow, int endCol);
    void clearSquare(int row, int col);
    
    //en passant
    int getEnPassantCol() const { return enPassantCol; }
    void setEnPassantCol(int col) { enPassantCol = col; }
    
    //castling
    bool canWshort() const {return !whiteKingMoved && !whiteKRookMoved;}
    bool canWlong() const {return !whiteKingMoved && !whiteQRookMoved;}
    bool canBshort() const {return !blackKingMoved && !blackKRookMoved;}
    bool canBlong() const {return !blackKingMoved && !blackQRookMoved;}
    };
