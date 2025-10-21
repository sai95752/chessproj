#include "game.h"


Game::Game() : selectedRow(-1), selectedCol(-1), pieceSelected(false), currentTurn(PIECE_COLOR::WHITE), awaitingPromotion(false), promotionRow(-1), promotionCol(-1), gameState(GAME_STATE::PLAYING) {}



void Game::handleClick(int row, int col) {
    if(row < 0 || row > 7 || col < 0 || col > 7) {
        return;
    }
    if (gameState == GAME_STATE::CHECKMATE || gameState == GAME_STATE::STALEMATE) {
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
        movePiece(row, col);
    }
}

void Game::selectPiece(int row, int col) {
    std::cout << "Piece Selected!" << std::endl;
    selectedRow = row;
    selectedCol = col;
    pieceSelected = true;
}



void Game::movePiece(int toRow, int toCol) {
    if (Validator::isValidMove(board, selectedRow, selectedCol, toRow, toCol)) {
            std::cout << "Successful move!" << std::endl;
            board.movePiece(selectedRow, selectedCol, toRow, toCol);
            checkPawnPromotion(toRow, toCol);
            switchTurn();
            deselectPiece();
            updateGameState();
        } else {
            std::cout << "Invalid move!" << std::endl;
            deselectPiece();
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






void Game::checkPawnPromotion(int row, int col) {
    Piece piece = board.getPiece(row, col);
    
    if (piece.type == PIECE_TYPE::PAWN) {
        bool shouldPromote = false;
        
        if(piece.color == PIECE_COLOR::WHITE && row == 0) {
            shouldPromote = true;
        } else if (piece.color == PIECE_COLOR::BLACK && row == 7) {
            shouldPromote = true;
        }
        if(shouldPromote) {
            awaitingPromotion = true;
            promotionRow = row;
            promotionCol = col;
            promotionColor = piece.color;
        }
    }
}

void Game::handlePromotionClick(const sf::RenderWindow& window, int mouseX, int mouseY, const Renderer &renderer) {
    if(!awaitingPromotion) return;
    PIECE_TYPE choice = renderer.getPromotionChoice(window, mouseX, mouseY, promotionColor);
    if(choice != PIECE_TYPE::NONE && choice != PIECE_TYPE::PAWN) {
        Piece promotedPiece(choice, promotionColor);
        board.setPiece(promotionRow, promotionCol, promotedPiece);
        
        awaitingPromotion = false;
        promotionRow = -1;
        promotionCol = -1;
        promotionColor = PIECE_COLOR::NONE;
        
        switchTurn();
    }
}

void Game::updateGameState() {
    gameState = Validator::getGameState(board, currentTurn);
    switch (gameState) {
        case GAME_STATE::CHECKMATE:
            std::cout << "Checkmate!" << std::endl;
            break;
        case GAME_STATE::STALEMATE:
            std::cout << "Stalemate!" << std::endl;
            break;
        case GAME_STATE::CHECK:
            std::cout << "Check" << std::endl;
            break;
        default:
            break;
    }
}
