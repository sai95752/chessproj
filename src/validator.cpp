#include "validator.h"

bool Validator::isValidMove(const Board& board, int fromRow, int fromCol, int toRow, int toCol) {
    if(!isWithinBounds(toRow, toCol)) {
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
    bool valid = false;
    switch (piece.type) {
        case PIECE_TYPE::PAWN:
            valid = isValidPawnMove(board, fromRow, fromCol, toRow, toCol);
            break;
        case PIECE_TYPE::ROOK:
            valid = isValidRookMove(board, fromRow, fromCol, toRow, toCol);
            break;
        case PIECE_TYPE::KNIGHT:
            valid = isValidKnightMove(board, fromRow, fromCol, toRow, toCol);
            break;
        case PIECE_TYPE::BISHOP:
            valid = isValidBishopMove(board, fromRow, fromCol, toRow, toCol);
            break;
        case PIECE_TYPE::QUEEN:
            valid = isValidQueenMove(board, fromRow, fromCol, toRow, toCol);
            break;
        case PIECE_TYPE::KING:
            valid = isValidKingMove(board, fromRow, fromCol, toRow, toCol);
            break;
        default:
             return false;
    }
    if(!valid) {
        return false;
    }
    
    return !illegalByCheck(board, fromRow, fromCol, toRow, toCol);
}

bool Validator::isWithinBounds(int row, int col) {
    return row >= 0 && row < 8 && col >= 0 && col < 8;
}

bool Validator::isPathClear(const Board& board, int fromRow, int fromCol, int toRow, int toCol) {
    int rowDir = (toRow > fromRow) ? 1 : (toRow < fromRow) ? -1 : 0;
    int colDir = (toCol > fromCol) ? 1 : (toCol < fromCol) ? -1 : 0;
    int currRow = fromRow + rowDir;
    int currCol = fromCol + colDir;
    while(currRow != toRow || currCol != toCol) {
        if(!board.getPiece(currRow, currCol).isEmpty()) {
            return false;
        }
        currRow += rowDir;
        currCol += colDir;
    }
    return true;
}
//regular pieces

// left, right, up, down
bool Validator::isValidRookMove(const Board& board, int fromRow, int fromCol, int toRow, int toCol) {
    if (fromRow == toRow || fromCol == toCol) {
            return isPathClear(board, fromRow, fromCol, toRow, toCol);
        }
    return false;
}
//diagonals
bool Validator::isValidBishopMove(const Board& board, int fromRow, int fromCol, int toRow, int toCol) {
    int rowDiff = abs(toRow - fromRow);
    int colDiff = abs(toCol - fromCol);
    return colDiff == rowDiff && isPathClear(board, fromRow, fromCol, toRow, toCol);
}
bool Validator::isValidQueenMove(const Board& board, int fromRow, int fromCol, int toRow, int toCol) {
    return isValidBishopMove(board, fromRow, fromCol, toRow, toCol) || isValidRookMove(board, fromRow, fromCol, toRow, toCol);
}



bool Validator::isValidPawnMove(const Board& board, int fromRow, int fromCol, int toRow, int toCol) {
    Piece pawn = board.getPiece(fromRow, fromCol);
    int dir = (pawn.color == PIECE_COLOR::WHITE) ? -1 : 1;
    int rowDiff = toRow - fromRow;
    int colDiff = abs(toCol - fromCol);
    Piece target = board.getPiece(toRow, toCol);
    if(rowDiff == dir && colDiff == 0 && target.isEmpty()) {
        return true;
    }
    //2 square move
    int startRow = (pawn.color == PIECE_COLOR::WHITE) ? 6 : 1;
    if(fromRow == startRow && rowDiff == 2 * dir && colDiff == 0 && target.isEmpty()) {
        int middleRow = fromRow + dir;
        if(!board.getPiece(middleRow, fromCol).isEmpty()) {
            return false;
        }
        return true;
    }
    //capture
    if(rowDiff == dir && colDiff == 1 && !target.isEmpty() && target.color != pawn.color) {
        return true;
    }
    //en passant
    if(rowDiff == dir && colDiff == 1 && target.isEmpty()) {
        int enPassantRow = (pawn.color == PIECE_COLOR::WHITE) ? 3 : 4;
        if(fromRow == enPassantRow && board.getEnPassantCol() == toCol) {
            Piece adjPawn = board.getPiece(fromRow, toCol);
            if(!adjPawn.isEmpty() && adjPawn.type == PIECE_TYPE::PAWN && adjPawn.color != pawn.color) {
                return true;
            }
        }
    }
    return false;
}
bool Validator::isValidKnightMove(const Board& board, int fromRow, int fromCol, int toRow, int toCol) {
    int rowDiff = abs(toRow - fromRow);
    int colDiff = abs(toCol - fromCol);
    return (rowDiff == 2 && colDiff == 1) || (colDiff == 2 && rowDiff == 1);
}
bool Validator::isValidKingMove(const Board& board, int fromRow, int fromCol, int toRow, int toCol) {
    //castling added
    int rowDiff = abs(toRow - fromRow);
    int colDiff = abs(toCol - fromCol);
    if((rowDiff <= 1 && colDiff <= 1) && (rowDiff + colDiff > 0)) {
        return true;
    }
    if(rowDiff == 0 && colDiff == 2) {
        return canCastle(board, fromRow, fromCol, toRow, toCol);
    }
    return false;
}

bool Validator::canCastle(const Board& board, int fromRow, int fromCol, int toRow, int toCol) {
    Piece king = board.getPiece(fromRow, fromCol);
    if(fromRow != toRow || abs(toCol - fromCol) != 2) {
        return false;
    }
    bool kingSide = (toCol > fromCol);
    if(king.color == PIECE_COLOR::WHITE) {
        if (fromRow != 7 || fromCol != 4) return false;
        if(kingSide && !board.canWshort()) return false;
        if(!kingSide && !board.canWlong()) return false;
    } else {
        if (fromRow != 0 || fromCol != 4) return false;
        if(kingSide && !board.canBshort()) return false;
        if(!kingSide && !board.canBlong()) return false;
    }
    
    int rookCol = kingSide ? 7 : 0;
    int dir = kingSide ? 1 : -1;
    
    for(int col = fromCol + dir; col != rookCol; col+= dir) {
        if(!board.getPiece(fromRow, col).isEmpty()) return false;
    }
    if(isKingInCheck(board, king.color)) return false;
    
    //check passthru
    int passCol = fromCol + dir;
    Board temp = board;
    temp.movePiece(fromRow, fromCol, fromRow, passCol);
    if(isKingInCheck(temp, king.color)) return false;
    
    //final square validity checked by isValidMove using isKingInCheck;
    
    return true;
}


std::pair<int, int> Validator::findKing(const Board &board, PIECE_COLOR color) {
    for(int row = 0; row < 8; row++) {
        for(int col = 0; col < 8; col++) {
            Piece piece = board.getPiece(row, col);
            if(piece.type == PIECE_TYPE::KING && piece.color == color) {
                return {row, col};
            }
        }
    }
    return {-1, -1};
}

bool Validator::isKingInCheck(const Board &board, PIECE_COLOR kingColor) {
    auto [kingRow, kingCol] = findKing(board, kingColor);
    PIECE_COLOR opponent = (kingColor == PIECE_COLOR::WHITE) ? PIECE_COLOR::BLACK : PIECE_COLOR::WHITE;
    for(int row = 0; row < 8; row++) {
        for(int col = 0; col < 8; col++) {
            Piece piece = board.getPiece(row, col);
            if(piece.isEmpty() || piece.color != opponent) {
                continue;
            }
            
            bool canAttack = false;
            switch (piece.type) {
                case PIECE_TYPE::PAWN:
                    canAttack = isValidPawnMove(board, row, col, kingRow, kingCol);
                    break;
                case PIECE_TYPE::ROOK:
                    canAttack = isValidRookMove(board, row, col, kingRow, kingCol);
                    break;
                case PIECE_TYPE::KNIGHT:
                    canAttack = isValidKnightMove(board, row, col, kingRow, kingCol);
                    break;
                case PIECE_TYPE::BISHOP:
                    canAttack = isValidBishopMove(board, row, col, kingRow, kingCol);
                    break;
                case PIECE_TYPE::QUEEN:
                    canAttack = isValidQueenMove(board, row, col, kingRow, kingCol);
                    break;
                case PIECE_TYPE::KING:
                    canAttack = isValidKingMove(board, row, col, kingRow, kingCol);
                    break;
                default:
                    break;
            }
            if(canAttack) return true;
        }
    }
    return false;
}

bool Validator::illegalByCheck(const Board& board, int fromRow, int fromCol, int toRow, int toCol) {
    Board tempBoard = board;
    Piece piece = tempBoard.getPiece(fromRow, fromCol);
    tempBoard.movePiece(fromRow, fromCol, toRow, toCol);
    return isKingInCheck(tempBoard, piece.color);
}

bool Validator::isCheckmate(const Board& board, PIECE_COLOR color) {
    if (!isKingInCheck(board, color)) {
        return false;
    }
    return !hasAnyLegalMove(board, color);
}

bool Validator::isStalemate(const Board& board, PIECE_COLOR color) {
    if (isKingInCheck(board, color)) {
        return false;
    }
    return !hasAnyLegalMove(board, color);
}

bool Validator::hasAnyLegalMove(const Board& board, PIECE_COLOR color) {
    for (int fromRow = 0; fromRow < 8; fromRow++) {
        for (int fromCol = 0; fromCol < 8; fromCol++) {
            Piece piece = board.getPiece(fromRow, fromCol);
            if (piece.isEmpty() || piece.color != color) {
                continue;
            }
            for (int toRow = 0; toRow < 8; toRow++) {
                for (int toCol = 0; toCol < 8; toCol++) {
                    if (isValidMove(board, fromRow, fromCol, toRow, toCol)) {
                        return true;
                    }
                }
            }
        }
    }
    return false;
}
GAME_STATE Validator::getGameState(const Board& board, PIECE_COLOR currentTurn) {
    if (isCheckmate(board, currentTurn)) {
        return GAME_STATE::CHECKMATE;
    }
    if (isStalemate(board, currentTurn)) {
        return GAME_STATE::STALEMATE;
    }
    if (isKingInCheck(board, currentTurn)) {
        return GAME_STATE::CHECK;
    }
    return GAME_STATE::PLAYING;
}
