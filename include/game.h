#pragma once
#include "board.h"
#include "game.h"
#include "validator.h"
#include "renderer.h"
#include <iostream>

class Game {
private:
    Board board;
    int selectedRow;
    int selectedCol;
    bool pieceSelected;
    PIECE_COLOR currentTurn;
    GAME_STATE gameState;
    
    //promotion stuffs
    bool awaitingPromotion;
    int promotionRow;
    int promotionCol;
    PIECE_COLOR promotionColor;
        
    void updateGameState();
    void selectPiece(int row, int col);
    void movePiece(int toRow, int toCol);
    void deselectPiece();
    void switchTurn();
    void checkPawnPromotion(int row, int col);
    

public:
    Game();
    
    void handleClick(int row, int col);
    void handlePromotionClick(const sf::RenderWindow& window, int mouseX, int mouseY, const Renderer& renderer);
    
    
    const Board& getBoard() const {return board;}
    bool isPieceSelected() const {return pieceSelected;}
    int getSelectedRow() const {return selectedRow;}
    int getSelectedCol() const {return selectedCol;}
    PIECE_COLOR getCurrentTurn() const {return currentTurn;}
    GAME_STATE getGameState() const {return gameState;}
    
    //promotions
    bool isAwaitingPromotion() const {return awaitingPromotion;}
    PIECE_COLOR getPromotionColor() const {return promotionColor;}
    
};
