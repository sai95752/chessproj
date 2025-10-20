#pragma once
#include "board.h"
#include <iostream>

class Game {
private:
    Board board;
    int selectedRow;
    int selectedCol;
    bool pieceSelected;
    
    PIECE_COLOR currentTurn;
    
    void selectPiece(int row, int col);
    void movePiece(int toRow, int toCol);
    void deselectPiece();
    void switchTurn();
    
public:
    Game();
    
    void handleClick(int row, int col);
    
    const Board& getBoard() const {return board;}
    bool isPieceSelected() const {return pieceSelected;}
    int getSelectedRow() const {return selectedRow;}
    int getSelectedCol() const {return selectedCol;}
    PIECE_COLOR getCurrentTurn() const {return currentTurn;}
};
