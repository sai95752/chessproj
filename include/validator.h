#pragma once
#include "board.h"
#include "piece.h"
#include <utility>
#include <vector>
#include <cmath>


enum class GAME_STATE {
    PLAYING,
    CHECK,
    CHECKMATE,
    STALEMATE
};


class Validator {
private:
    static bool isValidPawnMove(const Board& board, int fromRow, int fromCol, int toRow, int toCol);
    static bool isValidRookMove(const Board& board, int fromRow, int fromCol, int toRow, int toCol);
    static bool isValidKnightMove(const Board& board, int fromRow, int fromCol, int toRow, int toCol);
    static bool isValidBishopMove(const Board& board, int fromRow, int fromCol, int toRow, int toCol);
    static bool isValidQueenMove(const Board& board, int fromRow, int fromCol, int toRow, int toCol);
    static bool isValidKingMove(const Board& board, int fromRow, int fromCol, int toRow, int toCol);
    static bool isPathClear(const Board& board, int fromRow, int fromCol, int toRow, int toCol);
    static bool isWithinBounds(int row, int col);
    static std::pair<int, int> findKing(const Board& board, PIECE_COLOR color);
public:
    static bool isValidMove(const Board& board, int fromRow, int fromCol, int toRow, int toCol);
    static bool isKingInCheck(const Board& board, PIECE_COLOR kingColor);
    static bool illegalByCheck(const Board& board, int fromRow, int fromCol, int toRow, int toCol);
    
    //castling
    static bool canCastle(const Board& board, int fromRow, int fromCol, int toRow, int toCol);
    
    //checkmate or stalemate
    static bool isCheckmate(const Board& board, PIECE_COLOR color);
    static bool isStalemate(const Board& board, PIECE_COLOR color);
    static bool hasAnyLegalMove(const Board& board, PIECE_COLOR color);
    static GAME_STATE getGameState(const Board& board, PIECE_COLOR currentTurn);
    
};

