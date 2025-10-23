#include "renderer.h"


Renderer::Renderer(const sf::RenderWindow& window, Theme& theme)
: LIGHT_COLOR(theme.getLc()),
  DARK_COLOR(theme.getDc()),
  HIGHLIGHT_COLOR(theme.getHc()) {
    auto clamp = [](int v){ return std::max(0, std::min(255, v)); };
    auto dull = [&](sf::Color c, float factor){
        auto blend = [&](int comp){
            int target = 128;
            int val = static_cast<int>(comp + (target - comp) * factor);
            return static_cast<uint8_t>(clamp(val));
        };
        return sf::Color(blend(c.r), blend(c.g), blend(c.b), c.a);
    };

    const float dullFactor = 0.25f; // 0=no change, 1=fully gray
    sf::Color dulledLight = dull(LIGHT_COLOR, dullFactor);
    sf::Color dulledDark  = dull(DARK_COLOR,  dullFactor);

    lightSquare.setFillColor(dulledLight);
    darkSquare.setFillColor(dulledDark);

    // Derive piece colors with smaller offsets and then dull slightly
    auto adjust = [&](sf::Color c, int delta) {
        return sf::Color(
            static_cast<uint8_t>(clamp(static_cast<int>(c.r) + delta)),
            static_cast<uint8_t>(clamp(static_cast<int>(c.g) + delta)),
            static_cast<uint8_t>(clamp(static_cast<int>(c.b) + delta))
        );
    };
    PIECE_WHITE_COLOR = sf::Color::White;
    PIECE_BLACK_COLOR = sf::Color::Black;
    
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
            square.setPosition(sf::Vector2f(BOARD_OFFSET_X + col * SQUARE_SIZE, row * SQUARE_SIZE));
            window.draw(square);
        }
    }
}

void Renderer::drawPieces(sf::RenderWindow& window, const Board& board) {
    if(!fontLoaded) return;
    std::map<PIECE_TYPE, std::map<PIECE_COLOR, std::wstring>> pieceSymbols = {
        {PIECE_TYPE::KING,   {{PIECE_COLOR::WHITE, L"♚"}, {PIECE_COLOR::BLACK, L"♚"}}},
        {PIECE_TYPE::QUEEN,  {{PIECE_COLOR::WHITE, L"♛"}, {PIECE_COLOR::BLACK, L"♛"}}},
        {PIECE_TYPE::ROOK,   {{PIECE_COLOR::WHITE, L"♜"}, {PIECE_COLOR::BLACK, L"♜"}}},
        {PIECE_TYPE::BISHOP, {{PIECE_COLOR::WHITE, L"♝"}, {PIECE_COLOR::BLACK, L"♝"}}},
        {PIECE_TYPE::KNIGHT, {{PIECE_COLOR::WHITE, L"♞"}, {PIECE_COLOR::BLACK, L"♞"}}},
        {PIECE_TYPE::PAWN,   {{PIECE_COLOR::WHITE, L"♟"}, {PIECE_COLOR::BLACK, L"♟"}}}
    };
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            Piece piece = board.getPiece(row, col);
            if (!piece.isEmpty()) {
                sf::Text text(font);
                text.setString(pieceSymbols[piece.type][piece.color]);
                text.setCharacterSize(static_cast<unsigned int>(SQUARE_SIZE * 0.7f));
                
                // derive piece color from theme (opposite square color, slightly offset)
                if (piece.color == PIECE_COLOR::WHITE) {
                    text.setFillColor(PIECE_WHITE_COLOR);
                } else {
                    text.setFillColor(PIECE_BLACK_COLOR);
                }
                
                sf::FloatRect bounds = text.getLocalBounds();
                text.setOrigin(sf::Vector2f(bounds.position.x + bounds.size.x / 2.0f,
                                          bounds.position.y + bounds.size.y / 2.0f));
                text.setPosition(
                    sf::Vector2f(
                        BOARD_OFFSET_X + col * SQUARE_SIZE + SQUARE_SIZE / 2.0f,
                        row * SQUARE_SIZE + SQUARE_SIZE / 2.0f
                    )
                );
                
                window.draw(text);
            }
        }
    }
}

void Renderer::drawHighlight(sf::RenderWindow& window, int row, int col) {
    highlightSquare.setPosition(sf::Vector2f(BOARD_OFFSET_X + col * SQUARE_SIZE, row * SQUARE_SIZE));
    window.draw(highlightSquare);
}

void Renderer::updateSize(const sf::RenderWindow& window) {
    auto windowSize = window.getSize();
    //board uses the height of the window
    SQUARE_SIZE = windowSize.y / 8.0f;
    //position board on the right side, leaving 400px for left panel
    BOARD_OFFSET_X = windowSize.x - (SQUARE_SIZE * 8);

    lightSquare.setSize(sf::Vector2f(SQUARE_SIZE, SQUARE_SIZE));
    darkSquare.setSize(sf::Vector2f(SQUARE_SIZE, SQUARE_SIZE));
    highlightSquare.setSize(sf::Vector2f(SQUARE_SIZE, SQUARE_SIZE));

    // keep board squares dulled consistently with constructor
    auto clamp = [](int v){ return std::max(0, std::min(255, v)); };
    auto dull = [&](sf::Color c, float factor){
        auto blend = [&](int comp){
            int target = 128;
            int val = static_cast<int>(comp + (target - comp) * factor);
            return static_cast<uint8_t>(clamp(val));
        };
        return sf::Color(blend(c.r), blend(c.g), blend(c.b), c.a);
    };
    const float dullFactor = 0.25f;
    lightSquare.setFillColor(dull(LIGHT_COLOR, dullFactor));
    darkSquare.setFillColor(dull(DARK_COLOR, dullFactor));
    highlightSquare.setFillColor(HIGHLIGHT_COLOR);
}

void Renderer::drawPromoteDialog(sf::RenderWindow& window, PIECE_COLOR color) {
    //get the current view size instead of full window size
    sf::View currentView = window.getView();
    sf::FloatRect viewRect = currentView.getViewport();
    sf::Vector2u windowSize = window.getSize();
    float viewWidth = viewRect.size.x * windowSize.x;
    float viewHeight = viewRect.size.y * windowSize.y;

    auto clamp = [](int v){ return std::max(0, std::min(255, v)); };
    auto dull = [&](sf::Color c, float factor){
        auto blend = [&](int comp){
            int target = 128;
            int val = static_cast<int>(comp + (target - comp) * factor);
            return static_cast<uint8_t>(clamp(val));
        };
        return sf::Color(blend(c.r), blend(c.g), blend(c.b), c.a);
    };
    const float uiDull = 0.25f;
    sf::Color panelBg = dull(LIGHT_COLOR, uiDull);    // dialog background
    sf::Color panelOutline = dull(sf::Color::Black, 0.35f);
    sf::Color boxBg = dull(DARK_COLOR, uiDull);
    sf::Color boxOutline = dull(sf::Color::Black, 0.35f);

    sf::RectangleShape overlay(sf::Vector2f(viewWidth, viewHeight));
    overlay.setFillColor(sf::Color(0, 0, 0, 110));
    window.draw(overlay);
    
    float dialogWidth = SQUARE_SIZE * 4;
    float dialogHeight = SQUARE_SIZE * 1.5f;
    
    float dialogX = (viewWidth - dialogWidth) / 2;
    float dialogY = (viewHeight - dialogHeight) / 2;
    
    sf::RectangleShape dialogBox(sf::Vector2f(dialogWidth, dialogHeight));
    dialogBox.setPosition(sf::Vector2f(dialogX, dialogY));
    //tie to theme struct later
    dialogBox.setFillColor(panelBg);
    dialogBox.setOutlineColor(panelOutline);
    dialogBox.setOutlineThickness(3);
    window.draw(dialogBox);
    
    std::vector<PIECE_TYPE> pieces = {PIECE_TYPE::QUEEN, PIECE_TYPE::ROOK, PIECE_TYPE::BISHOP, PIECE_TYPE::KNIGHT};
    std::map<PIECE_TYPE, std::map<PIECE_COLOR, std::wstring>> pieceSymbols = {
        {PIECE_TYPE::QUEEN,  {{PIECE_COLOR::WHITE, L"♛"}, {PIECE_COLOR::BLACK, L"♛"}}},
        {PIECE_TYPE::ROOK,   {{PIECE_COLOR::WHITE, L"♜"}, {PIECE_COLOR::BLACK, L"♜"}}},
        {PIECE_TYPE::BISHOP, {{PIECE_COLOR::WHITE, L"♝"}, {PIECE_COLOR::BLACK, L"♝"}}},
        {PIECE_TYPE::KNIGHT, {{PIECE_COLOR::WHITE, L"♞"}, {PIECE_COLOR::BLACK, L"♞"}}}
    };
    
    //position piece boxes correctly
    float boxY = dialogY + (dialogHeight - SQUARE_SIZE) / 2;
    for(size_t i = 0; i < pieces.size(); i++) {
        sf::RectangleShape pieceBox(sf::Vector2f(SQUARE_SIZE, SQUARE_SIZE));
        float boxX = dialogX + i * SQUARE_SIZE;
        pieceBox.setPosition(sf::Vector2f(boxX, boxY));
        pieceBox.setFillColor(boxBg);
        pieceBox.setOutlineColor(boxOutline);
        pieceBox.setOutlineThickness(2);
        window.draw(pieceBox);
        
        if(fontLoaded) {
            sf::Text text(font);
            text.setString(pieceSymbols[pieces[i]][color]);
            text.setCharacterSize(static_cast<unsigned int>(SQUARE_SIZE * .7f));
            if (color == PIECE_COLOR::WHITE) {
                text.setFillColor(PIECE_WHITE_COLOR);
            } else {
                text.setFillColor(PIECE_BLACK_COLOR);
            }
            
            sf::FloatRect bounds = text.getLocalBounds();
            text.setOrigin(sf::Vector2f(bounds.size.x / 2.0f, bounds.size.y / 2.0f));
            text.setPosition(sf::Vector2f(boxX + SQUARE_SIZE / 2.0f, boxY + SQUARE_SIZE / 2.0f));
            window.draw(text);
        }
    }
}

PIECE_TYPE Renderer::getPromotionChoice(const sf::RenderWindow& window, int mouseX, int mouseY, PIECE_COLOR color) const {
    //get the current view size instead of full window size
    sf::View currentView = window.getView();
    sf::FloatRect viewRect = currentView.getViewport();
    sf::Vector2u windowSize = window.getSize();
    float viewWidth = viewRect.size.x * windowSize.x;
    float viewHeight = viewRect.size.y * windowSize.y;
    
    float dialogWidth = SQUARE_SIZE * 4;
    float dialogHeight = SQUARE_SIZE * 1.5f;
    
    //center the dialog properly (same as in drawPromoteDialog)
    float dialogX = (viewWidth - dialogWidth) / 2;
    float dialogY = (viewHeight - dialogHeight) / 2;
    float boxY = dialogY + (dialogHeight - SQUARE_SIZE) / 2;
    
    if (mouseY >= boxY && mouseY <= boxY + SQUARE_SIZE) {
        for (int i = 0; i < 4; i++) {
            float boxX = dialogX + i * SQUARE_SIZE;
            if (mouseX >= boxX && mouseX <= boxX + SQUARE_SIZE) {
                switch (i) {
                    case 0: return PIECE_TYPE::QUEEN;
                    case 1: return PIECE_TYPE::ROOK;
                    case 2: return PIECE_TYPE::BISHOP;
                    case 3: return PIECE_TYPE::KNIGHT;
                }
            }
        }
    }
    return PIECE_TYPE::NONE;
}


void Renderer::drawGameOver(sf::RenderWindow& window, GAME_STATE state, PIECE_COLOR loser) {
    if (state != GAME_STATE::CHECKMATE && state != GAME_STATE::STALEMATE) {
        return;
    }

    auto clamp = [](int v){ return std::max(0, std::min(255, v)); };
    auto dull = [&](sf::Color c, float factor){
        auto blend = [&](int comp){
            int target = 128;
            int val = static_cast<int>(comp + (target - comp) * factor);
            return static_cast<uint8_t>(clamp(val));
        };
        return sf::Color(blend(c.r), blend(c.g), blend(c.b), c.a);
    };
    const float uiDull = 0.25f;
    sf::Color panelBg = dull(LIGHT_COLOR, uiDull);
    sf::Color panelOutline = dull(sf::Color::Black, 0.35f);
    sf::Color primaryText = dull(sf::Color::Black, 0.25f);
    sf::Color secondaryText = dull(sf::Color(100,100,100), 0.2f);
    
    //semi-transparent dark overlay
    sf::RectangleShape overlay(sf::Vector2f(window.getSize().x, window.getSize().y));
    overlay.setFillColor(sf::Color(0, 0, 0, 160));
    window.draw(overlay);
    
    //message box
    float boxWidth = 400;
    float boxHeight = 200;
    float boxX = (window.getSize().x - boxWidth) / 2;
    float boxY = (window.getSize().y - boxHeight) / 2;
    
    sf::RectangleShape messageBox(sf::Vector2f(boxWidth, boxHeight));
    messageBox.setPosition(sf::Vector2f(boxX, boxY));
    messageBox.setFillColor(panelBg);
    messageBox.setOutlineColor(panelOutline);
    messageBox.setOutlineThickness(5);
    window.draw(messageBox);
    if (fontLoaded) {
        sf::Text mainText(font);
        if (state == GAME_STATE::CHECKMATE) {
            std::string winner = (loser == PIECE_COLOR::WHITE) ? "Black" : "White";
            mainText.setString("Checkmate!\n\n" + winner + " Wins!");
        } else {
            mainText.setString("Stalemate!\n\nDraw!");
        }
        
        mainText.setCharacterSize(40);
        mainText.setFillColor(primaryText);
        mainText.setStyle(sf::Text::Bold);
        
        //centering
        sf::FloatRect textBounds = mainText.getLocalBounds();
        mainText.setOrigin(sf::Vector2f(textBounds.size.x / 2.0f, textBounds.size.y / 2.0f));
        mainText.setPosition(
            sf::Vector2f(boxX + boxWidth / 2.0f,
            boxY + boxHeight / 2.0f - 20)
        );
        
        window.draw(mainText);        
        sf::Text restartText(font);
        restartText.setString("Press R to restart");
        restartText.setCharacterSize(20);
        restartText.setFillColor(secondaryText);
        
        sf::FloatRect restartBounds = restartText.getLocalBounds();
        restartText.setOrigin(sf::Vector2f(restartBounds.size.x / 2.0f, restartBounds.size.y / 2.0f));
        restartText.setPosition(
            sf::Vector2f(boxX + boxWidth / 2.0f,
            boxY + boxHeight - 40)
        );
        
        window.draw(restartText);
    }
}
void Renderer::refreshTheme(const Theme& theme) {
    LIGHT_COLOR = theme.getLc();
    DARK_COLOR = theme.getDc();
    HIGHLIGHT_COLOR = theme.getHc();

    auto clamp = [](int v){ return std::max(0, std::min(255, v)); };
    auto dull = [&](sf::Color c, float factor){
        auto blend = [&](int comp){
            int target = 128;
            int val = static_cast<int>(comp + (target - comp) * factor);
            return static_cast<uint8_t>(clamp(val));
        };
        return sf::Color(blend(c.r), blend(c.g), blend(c.b), c.a);
    };
    const float dullFactor = 0.25f;
    sf::Color dulledLight = dull(LIGHT_COLOR, dullFactor);
    sf::Color dulledDark  = dull(DARK_COLOR,  dullFactor);

    lightSquare.setFillColor(dulledLight);
    darkSquare.setFillColor(dulledDark);
    highlightSquare.setFillColor(HIGHLIGHT_COLOR);

    auto adjust = [&](sf::Color c, int delta) {
        return sf::Color(
            static_cast<uint8_t>(clamp(static_cast<int>(c.r) + delta)),
            static_cast<uint8_t>(clamp(static_cast<int>(c.g) + delta)),
            static_cast<uint8_t>(clamp(static_cast<int>(c.b) + delta))
        );
    };
}

