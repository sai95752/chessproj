#include "validator.h"
#include <cmath>

bool Validator::isValidMove(const Board& board, int fromRow, int fromCol, int toRow, int toCol) {
    if(!isWithinBounds(toCol, toCol)) {
        return false;
    }
    if(fromRow == toRow && fromCol == toCol) {
        return false;
    }
    Piece piece = board.getPiece(fromRow, fromCol);
    Piece target = board.getPiece(toRow, toCol);
    if(!target.isEmpty() && target.color == piece.color) {
        return false;
    }
    switch (piece.type) {
        case PIECE_TYPE::PAWN:
            return isValidPawnMove(board, fromRow, fromCol, toRow, toCol, piece.color);
        case PIECE_TYPE::ROOK:
            return isValidRookMove(board, fromRow, fromCol, toRow, toCol, piece.color);
        case PIECE_TYPE::KNIGHT:
            return isValidKnightMove(board, fromRow, fromCol, toRow, toCol, piece.color);
        case PIECE_TYPE::BISHOP:
            return isValidBishopMove(board, fromRow, fromCol, toRow, toCol, piece.color);
        case PIECE_TYPE::QUEEN:
            return isValidQueenMove(board, fromRow, fromCol, toRow, toCol, piece.color);
        case PIECE_TYPE::KING:
            return isValidKingMove(board, fromRow, fromCol, toRow, toCol, piece.color);
        default:
            return false;
    }
}

bool Validator::isWithinBounds(int row, int col) {
    return row >= 0 && row < 8 && col >= 0 && col < 8;
}

bool Validator::isPathClear(int fromRow, int fromCol, int toRow, int toCol) {
    
}
