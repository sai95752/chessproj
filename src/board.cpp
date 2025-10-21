#include "board.h"

Board::Board() {
    enPassantCol = -1;
    whiteKingMoved = false;
    whiteKRookMoved = false;
    whiteQRookMoved = false;
    blackKingMoved = false;
    blackKRookMoved = false;
    blackQRookMoved = false;
    initialize();
}

Board::Board(const Board& other) {
    for(int row = 0; row < 8; row++) {
        for(int col = 0; col < 8; col++)
            grid[row][col] = other.grid[row][col];
    }
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
    Piece piece = getPiece(startRow, startCol);
    if(!piece.isEmpty()) {
        if(piece.type == PIECE_TYPE::KING) {
            if(piece.color == PIECE_COLOR::WHITE) {
                whiteKingMoved = true;
            } else if(piece.color == PIECE_COLOR::BLACK) {
                blackKingMoved = true;
            }
            
            if(abs(endCol - startCol) == 2) {
                if(endCol > startCol) {
                    int rookRow = startRow;
                    movePiece(rookRow, 7, rookRow, endCol - 1);
                }
            } else {
                int rookRow = startRow;
                movePiece(rookRow, 0, rookRow, endCol + 1);
            }
        }
        
        //rook move checker
        if(piece.type == PIECE_TYPE::ROOK) {
            if(piece.color == PIECE_COLOR::WHITE) {
                if(startRow == 7 && startCol == 7) whiteKRookMoved = true;
                if(startRow == 7 && startCol == 0) whiteQRookMoved = true;
            } else {
                if(startRow == 0 && startCol == 7) blackKRookMoved = true;
                if(startRow == 0 && startCol == 0) blackQRookMoved = true;
            }
        }
        
        //en passant checker
        if(piece.type == PIECE_TYPE::PAWN && abs(startRow - endRow) == 2) {
            enPassantCol = startCol;
        } else {
            enPassantCol = -1;
        }
        if (piece.type == PIECE_TYPE::PAWN && startCol != endCol && getPiece(endRow, endCol).isEmpty()) {
            //en passant
            int capturedPawnRow = (piece.color == PIECE_COLOR::WHITE) ? endRow + 1 : endRow - 1;
            clearSquare(capturedPawnRow, endCol);
        }
        
        setPiece(endRow, endCol, piece);
        clearSquare(startRow, startCol);
        return true;
    }
    return false;
}

void Board::clearSquare(int row, int col) {
    if(row >= 0 && row < 8 && col >= 0 && col < 8) setPiece(row, col, Piece());
}


