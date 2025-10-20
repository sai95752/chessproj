#include "board.h"

Board::Board() {
    initialize();
}

void Board::initialize() {
    for(int row = 0; row < 8; row++) {
        for(int col = 0; col < 8; col++) {
            grid[row][col] = Piece();
        }
    }
    //WHITE
    grid[7][0] = Piece(PIECE_TYPE::ROOK, PIECE_COLOR::WHITE);
    grid[7][7] = Piece(PIECE_TYPE::ROOK, PIECE_COLOR::WHITE);
    grid[7][1] = Piece(PIECE_TYPE::KNIGHT, PIECE_COLOR::WHITE);
    grid[7][6] = Piece(PIECE_TYPE::KNIGHT, PIECE_COLOR::WHITE);
    grid[7][2] = Piece(PIECE_TYPE::BISHOP, PIECE_COLOR::WHITE);
    grid[7][5] = Piece(PIECE_TYPE::BISHOP, PIECE_COLOR::WHITE);
    grid[7][3] = Piece(PIECE_TYPE::QUEEN, PIECE_COLOR::WHITE);
    grid[7][4] = Piece(PIECE_TYPE::KING, PIECE_COLOR::WHITE);
    for(auto& sq : grid[6]) {
        sq = Piece(PIECE_TYPE::PAWN, PIECE_COLOR::WHITE);
    }
    //BLACK
    grid[0][0] = Piece(PIECE_TYPE::ROOK, PIECE_COLOR::BLACK);
    grid[0][7] = Piece(PIECE_TYPE::ROOK, PIECE_COLOR::BLACK);
    grid[0][1] = Piece(PIECE_TYPE::KNIGHT, PIECE_COLOR::BLACK);
    grid[0][6] = Piece(PIECE_TYPE::KNIGHT, PIECE_COLOR::BLACK);
    grid[0][2] = Piece(PIECE_TYPE::BISHOP, PIECE_COLOR::BLACK);
    grid[0][5] = Piece(PIECE_TYPE::BISHOP, PIECE_COLOR::BLACK);
    grid[0][3] = Piece(PIECE_TYPE::QUEEN, PIECE_COLOR::BLACK);
    grid[0][4] = Piece(PIECE_TYPE::KING, PIECE_COLOR::BLACK);
    for(auto& sq : grid[1]) {
        sq = Piece(PIECE_TYPE::PAWN, PIECE_COLOR::BLACK);
    }
}

Piece Board::getPiece(int row, int col) const {
    if(row >= 0 && row < 8  && col >= 0 && col < 8) {
        return grid[row][col];
    }
    return Piece();
}

void Board::setPiece(int row, int col, const Piece& piece) {
    if(row >= 0 && row < 8 && col >= 0 && col < 8) grid[row][col] = piece;
}

bool Board:: movePiece(int startRow, int startCol, int endRow, int endCol) {
    Piece piece = Board::getPiece(startRow, startCol);
    if(!piece.isEmpty()) {
        Board::setPiece(endRow, endCol, piece);
        clearSquare(startRow, startCol);
        return true;
    }
    return false;
}

void Board::clearSquare(int row, int col) {
    if(row >= 0 && row < 8 && col >= 0 && col < 8) setPiece(row, col, Piece());
}
