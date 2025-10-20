#include <SFML/Graphics.hpp>
#include "theme.h"
#include "board.h"
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
    
    
    //consts
    static constexpr int BOARD_SIZE = 8;
    
    //colors
    sf::Font font;
    bool fontLoaded = false;
    sf::Color LIGHT_COLOR;
    sf::Color DARK_COLOR;
    sf::Color HIGHLIGHT_COLOR;

public:
    //constrcutor -> takes in window object
    Renderer(const sf::RenderWindow& window, Theme& theme);
    
    void draw(sf::RenderWindow& window, const Board& board);
    void drawBoard(sf::RenderWindow& window);
    void drawPieces(sf::RenderWindow& window, const Board& board);
    void drawHighlight(sf::RenderWindow& window, int row, int col);
    void updateSize(const sf::RenderWindow& window);
    
    float getSquareSize() const { return SQUARE_SIZE; }
};
