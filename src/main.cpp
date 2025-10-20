#include <SFML/Graphics.hpp>
#include "renderer.h"
#include "board.h"
#include "theme.h"
#include "game.h"


int main() {
    
    sf::RenderWindow window(sf::VideoMode({600u, 600u}), "Chess", sf::Style::Titlebar | sf::Style::Close);
    Theme myTheme = getTheme(ThemeType::DARK);
    Renderer renderer(window, myTheme);
    Board board;
    Game game;
    while (window.isOpen()) {
        //checking events
        while(auto event = window.pollEvent()) {
            if(event->is<sf::Event::Closed>()) {
                window.close();
            }
            if(event->is<sf::Event::Resized>()) {
                auto size = window.getSize();
                unsigned int sqSz = std::min(size.x, size.y);
                sf::FloatRect visibleArea({0, 0}, {static_cast<float>(sqSz), static_cast<float>(sqSz)});
                window.setView(sf::View(visibleArea));
                
            }
            if(event->is<sf::Event::MouseButtonPressed>()) {
                auto mouseEvent = event->getIf<sf::Event::MouseButtonPressed>();
                int row = mouseEvent->position.y / renderer.getSquareSize();
                int col = mouseEvent->position.x / renderer.getSquareSize();
                game.handleClick(row, col);
            }
        }
        
        window.clear(sf::Color::Black);

        renderer.draw(window, game.getBoard());
        if(game.isPieceSelected()) {
            renderer.drawHighlight(window, game.getSelectedRow(), game.getSelectedCol());
        }
        window.display();
    }

    return 0;
}
