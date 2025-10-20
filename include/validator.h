#pragma once
#include "board.h"
#include "piece.h"

class Validator {
private:
    static bool isValidPawnMove(const Board& board, int fromRow, int fromCol, int toRow, int toCol, PIECE_COLOR color);
    static bool isValidRookMove(const Board& board, int fromRow, int fromCol, int toRow, int toCol, PIECE_COLOR color);
    static bool isValidKnightMove(const Board& board, int fromRow, int fromCol, int toRow, int toCol, PIECE_COLOR color);
    static bool isValidBishopMove(const Board& board, int fromRow, int fromCol, int toRow, int toCol, PIECE_COLOR color);
    static bool isValidQueenMove(const Board& board, int fromRow, int fromCol, int toRow, int toCol, PIECE_COLOR color);
    static bool isValidKingMove(const Board& board, int fromRow, int fromCol, int toRow, int toCol, PIECE_COLOR color);
    static bool isPathClear(int fromRow, int fromCol, int toRow, int toCol);
    static bool isWithinBounds(int row, int col);
public:
    static bool isValidMove(const Board& board, int fromRow, int fromCol, int toRow, int toCol);
};

