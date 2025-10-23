#pragma once
#include <SFML/Graphics.hpp>
#include "theme.h"
#include "board.h"
#include "validator.h"
#include <map>
#include <optional>
#include <iostream>
class Renderer {
private:
    //sqrs
    sf::RectangleShape lightSquare;
    sf::RectangleShape darkSquare;
    sf::RectangleShape highlightSquare;
    
    //dynamic resize
    float SQUARE_SIZE;
    float BOARD_OFFSET_X;
    
    
    //consts
    static constexpr int BOARD_SIZE = 8;
    
    //colors
    sf::Font font;
    bool fontLoaded = false;
    sf::Color LIGHT_COLOR;
    sf::Color DARK_COLOR;
    sf::Color HIGHLIGHT_COLOR;
    sf::Color PIECE_WHITE_COLOR;
    sf::Color PIECE_BLACK_COLOR;

public:
    //constrcutor -> takes in window object
    Renderer(const sf::RenderWindow& window, Theme& theme);
    void refreshTheme(const Theme& theme);
    
    void draw(sf::RenderWindow& window, const Board& board);
    void drawBoard(sf::RenderWindow& window);
    void drawPieces(sf::RenderWindow& window, const Board& board);
    void drawHighlight(sf::RenderWindow& window, int row, int col);
    void drawPromoteDialog(sf::RenderWindow& window, PIECE_COLOR color);
    PIECE_TYPE getPromotionChoice(const sf::RenderWindow& window, int mouseX, int mouseY, PIECE_COLOR color) const;

    
    void updateSize(const sf::RenderWindow& window);
    float getSquareSize() const { return SQUARE_SIZE; }
    float getBoardOffsetX() const { return BOARD_OFFSET_X; }
    
    
    void drawGameOver(sf::RenderWindow& window, GAME_STATE state, PIECE_COLOR loser);
    
};

