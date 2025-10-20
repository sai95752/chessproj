#include "renderer.h"


Renderer::Renderer(const sf::RenderWindow& window, Theme& theme) : LIGHT_COLOR(theme.getLc()), DARK_COLOR(theme.getDc()), HIGHLIGHT_COLOR(theme.getHc()) {
    if(font.openFromFile("assets/fonts/DejaVuSans.ttf")) {
        fontLoaded = true;
        std::cout << "Pieces loaded successfully.";
    }
    else {
        std::cerr << "Failed to load pieces";
    }
    Renderer::updateSize(window);
}

void Renderer::draw(sf::RenderWindow& window, const Board& board) {
    drawBoard(window);
    drawPieces(window, board);
}

void Renderer::drawBoard(sf::RenderWindow& window) {
    for(int row = 0; row < BOARD_SIZE; row++) {
        for(int col = 0; col < BOARD_SIZE; col++) {
            sf::RectangleShape& square = ((row + col) % 2 == 0) ? lightSquare : darkSquare;
            square.setPosition(sf::Vector2f(col * SQUARE_SIZE, row * SQUARE_SIZE));
            window.draw(square);
        }
    }
}

void Renderer::drawPieces(sf::RenderWindow& window, const Board& board) {
    if(!fontLoaded) return;
    // Unicode chess piece symbols
    std::map<PIECE_TYPE, std::map<PIECE_COLOR, std::wstring>> pieceSymbols = {
        {PIECE_TYPE::KING,   {{PIECE_COLOR::WHITE, L"♔"}, {PIECE_COLOR::BLACK, L"♚"}}},
        {PIECE_TYPE::QUEEN,  {{PIECE_COLOR::WHITE, L"♕"}, {PIECE_COLOR::BLACK, L"♛"}}},
        {PIECE_TYPE::ROOK,   {{PIECE_COLOR::WHITE, L"♖"}, {PIECE_COLOR::BLACK, L"♜"}}},
        {PIECE_TYPE::BISHOP, {{PIECE_COLOR::WHITE, L"♗"}, {PIECE_COLOR::BLACK, L"♝"}}},
        {PIECE_TYPE::KNIGHT, {{PIECE_COLOR::WHITE, L"♘"}, {PIECE_COLOR::BLACK, L"♞"}}},
        {PIECE_TYPE::PAWN,   {{PIECE_COLOR::WHITE, L"♙"}, {PIECE_COLOR::BLACK, L"♟"}}}
    };
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            Piece piece = board.getPiece(row, col);
            if (!piece.isEmpty()) {
                sf::Text text(font);
                text.setString(pieceSymbols[piece.type][piece.color]);
                text.setCharacterSize(static_cast<unsigned int>(SQUARE_SIZE * 0.7f));
                text.setFillColor(sf::Color::Black);
                
                // Center the piece in the square
                sf::FloatRect bounds = text.getLocalBounds();
                text.setOrigin(sf::Vector2f(bounds.position.x + bounds.size.x / 2.0f,
                                          bounds.position.y + bounds.size.y / 2.0f));
                text.setPosition(
                    sf::Vector2f(
                        col * SQUARE_SIZE + SQUARE_SIZE / 2.0f,
                        row * SQUARE_SIZE + SQUARE_SIZE / 2.0f
                    )
                );
                
                window.draw(text);
            }
        }
    }
}

void Renderer::drawHighlight(sf::RenderWindow& window, int row, int col) {
    highlightSquare.setPosition(sf::Vector2f(col * SQUARE_SIZE, row * SQUARE_SIZE));
    window.draw(highlightSquare);
}

void Renderer::updateSize(const sf::RenderWindow& window) {
    auto windowSize = window.getSize();
    float minDimension = std::min(windowSize.x, windowSize.y);
    SQUARE_SIZE = minDimension / 8;
    lightSquare.setSize(sf::Vector2f(SQUARE_SIZE, SQUARE_SIZE));
    lightSquare.setFillColor(LIGHT_COLOR);
    darkSquare.setSize(sf::Vector2f(SQUARE_SIZE, SQUARE_SIZE));
    darkSquare.setFillColor(DARK_COLOR);
    highlightSquare.setSize(sf::Vector2f(SQUARE_SIZE, SQUARE_SIZE));
    highlightSquare.setFillColor(HIGHLIGHT_COLOR);
}
