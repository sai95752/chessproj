#pragma once

enum class PIECE_TYPE {
    NONE = 0,
    PAWN,
    KNIGHT,
    BISHOP,
    ROOK,
    QUEEN,
    KING
};
enum class PIECE_COLOR {
    NONE = 0,
    WHITE,
    BLACK
};

struct Piece {
    PIECE_TYPE type;
    PIECE_COLOR color;
    
    
    Piece () : type(PIECE_TYPE::NONE), color(PIECE_COLOR::NONE) {}
    Piece(PIECE_TYPE t, PIECE_COLOR c) : type(t), color(c) {}
    
    bool isEmpty() const { return type == PIECE_TYPE::NONE; }
};
