#include <SFML/Graphics.hpp>
#include "renderer.h"
#include "board.h"
#include "theme.h"
#include "game.h"

int main() {
    
    sf::RenderWindow window(sf::VideoMode({800u, 800u}), "Chess", sf::Style::Titlebar | sf::Style::Close);
    Theme myTheme = getTheme(ThemeType::BLUE);
    Renderer renderer(window, myTheme);
    Board board;
    Game game;
    while (window.isOpen()) {
        //checking events
        while(auto event = window.pollEvent()) {
            if(event->is<sf::Event::KeyPressed>()) {
                auto keyEvent = event->getIf<sf::Event::KeyPressed>();
                if(keyEvent->code == sf::Keyboard::Key::R) {
                    if(game.getGameState() == GAME_STATE::CHECKMATE || game.getGameState() == GAME_STATE::STALEMATE) {
                        game = Game();
                    }
                }
            }
            
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
                int mouseX = mouseEvent->position.x;
                int mouseY = mouseEvent->position.y;
                if(game.isAwaitingPromotion()) {
                    game.handlePromotionClick(window, mouseX, mouseY, renderer);
                }
                int row = mouseY / renderer.getSquareSize();
                int col = mouseX / renderer.getSquareSize();
                game.handleClick(row, col);
            }
        }
        
        window.clear(sf::Color::Black);

        renderer.draw(window, game.getBoard());
        if(game.isPieceSelected()) {
            renderer.drawHighlight(window, game.getSelectedRow(), game.getSelectedCol());
        }
        if(game.isAwaitingPromotion()) {
            renderer.drawPromoteDialog(window, game.getPromotionColor());
        }
        
        if (game.getGameState() == GAME_STATE::CHECKMATE ||
            game.getGameState() == GAME_STATE::STALEMATE) {
            renderer.drawGameOver(window, game.getGameState(), game.getCurrentTurn());
        }
        window.display();
    }

    return 0;
}
