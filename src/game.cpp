#include "game.h"

Game::Game() : selectedRow(-1), selectedCol(-1), pieceSelected(false), currentTurn(PIECE_COLOR::WHITE) {
}

void Game::handleClick(int row, int col) {
    if(row < 0 || row > 7 || col < 0 || col > 7) {
        return;
    }
    std::cout << "Click detected at row: " << row << ", col: " << col << std::endl;
    if (!pieceSelected) {
        std::cout << "No piece selected, trying to select..." << std::endl;
        
        Piece piece = board.getPiece(row, col);
        
        
        std::cout << "Piece isEmpty: " << piece.isEmpty() << std::endl;
        std::cout << "Piece color: " << static_cast<int>(piece.color) << std::endl;
        std::cout << "Current turn: " << static_cast<int>(currentTurn) << std::endl;
        
        
        
        if (!piece.isEmpty() && piece.color == currentTurn) {
            std::cout << "Selecting piece!" << std::endl;
            selectPiece(row, col);
        } else {
            std::cout << "Cannot select: piece is empty or wrong color" << std::endl;
        }
    }
    else {
        //validate
        movePiece(row, col);
        std::cout << "Success!";
    }
}

void Game::selectPiece(int row, int col) {
    std::cout << "Piece Selected!";
    selectedRow = row;
    selectedCol = col;
    pieceSelected = true;
}

void Game::movePiece(int toRow, int toCol) {
    //validate
    if(board.movePiece(selectedRow, selectedCol, toRow, toCol)) {
        std::cout << "Move successful!";
        switchTurn();
        deselectPiece();
    }
    else {
        std::cout << "Move failed!";
    }
}

void Game::deselectPiece() {
    selectedRow = -1;
    selectedCol  = -1;
    pieceSelected = false;
}

void Game::switchTurn() {
    currentTurn = (currentTurn == PIECE_COLOR::WHITE) ? PIECE_COLOR::BLACK : PIECE_COLOR::WHITE;
}

