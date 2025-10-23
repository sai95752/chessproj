#include <SFML/Graphics.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>
#include <TGUI/TGUI.hpp>
#include "renderer.h"
#include "board.h"
#include "theme.h"
#include "game.h"
#include "menu.h"

enum class APP_STATE {
    MAIN_MENU,
    PLAYING,
    PAUSED
};

int main() {
    sf::ContextSettings settings;
    settings.antiAliasingLevel = 8;  //smoother -> 8, ass -> 1
    sf::RenderWindow window(sf::VideoMode({1200u, 800u}), "Chess", sf::State(sf::Style::Titlebar | sf::Style::Close), settings);
    
    
    window.setView(window.getDefaultView());

    Theme myTheme = getTheme(ThemeType::DARK);

    tgui::Gui gui(window);
    Menu menu(gui, myTheme);
    GameUI gameUI(gui, myTheme);

    APP_STATE appState = APP_STATE::MAIN_MENU;
    menu.show();

    Renderer renderer(window, myTheme);
    Board board;
    Game game;
    while (window.isOpen()) {
        //checking events
        while(auto event = window.pollEvent()) {
            gui.handleEvent(*event);
    
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
                sf::FloatRect visibleArea({0, 0}, {static_cast<float>(size.x), static_cast<float>(size.y)});
                window.setView(sf::View(visibleArea));
                renderer.updateSize(window);
            }
            if(appState == APP_STATE::PLAYING && event->is<sf::Event::MouseButtonPressed>()) {
                auto mouseEvent = event->getIf<sf::Event::MouseButtonPressed>();
                int mouseX = mouseEvent->position.x;
                int mouseY = mouseEvent->position.y;
                if(game.isAwaitingPromotion()) {
                    game.handlePromotionClick(window, mouseX, mouseY, renderer);
                }
                int adjustedX = mouseX - renderer.getBoardOffsetX();
                if(adjustedX >= 0) {
                    int row = mouseY / renderer.getSquareSize();
                    int col = adjustedX / renderer.getSquareSize();
                    if(col >= 0 && col < 8 && row >= 0 && row < 8) {
                        game.handleClick(row, col);
                    }
                }
            }
        }
        
        if(appState == APP_STATE::MAIN_MENU) {
            MENU_CHOICE choice = menu.getChoice();

            if(menu.hasThemeChanged()) {
                ThemeType newThemeType = menu.getSelectedThemeType();
                myTheme = getTheme(newThemeType);
                renderer.refreshTheme(myTheme);
                renderer.updateSize(window);
                menu.hide();
                menu.show();
                menu.resetThemeChanged();
                //keep open
                menu.reopenSettingsDialog();
            }

            if(choice == MENU_CHOICE::SINGLE_PLAYER) {
                menu.hide();
                gameUI.show();
                appState = APP_STATE::PLAYING;
                game = Game();
                menu.resetChoice();
            } else if(choice == MENU_CHOICE::MULTIPLAYER) {
                menu.hide();
                gameUI.show();
                appState = APP_STATE::PLAYING;
                game = Game();
                menu.resetChoice();
            } else if(choice == MENU_CHOICE::QUIT) {
                window.close();
            }
        }
        
        if(appState == APP_STATE::PLAYING) {
            std::string turnColor = (game.getCurrentTurn() == PIECE_COLOR::WHITE) ? "White" : "Black";
            gameUI.updateTurn(turnColor);
            
            if(game.getGameState() == GAME_STATE::CHECK) {
                gameUI.updateStatus("Check!");
            } else {
                gameUI.updateStatus("");
            }
            
            if(game.getGameState() == GAME_STATE::CHECKMATE) {
                std::string winner = game.getCurrentTurn() == PIECE_COLOR::WHITE ? "Black" : "White";
                gameUI.showGameOverDialog(
                                          "Checkmate! " + winner + " wins!",
                                          [&] () {
                                              game = Game();
                                          },
                                          [&] () {
                                              gameUI.hide();
                                              menu.show();
                                              appState = APP_STATE::MAIN_MENU;
                                          }
                );
            } else if(game.getGameState() == GAME_STATE::STALEMATE) {
                std::string winner = game.getCurrentTurn() == PIECE_COLOR::WHITE ? "Black" : "White";
                gameUI.showGameOverDialog(
                                          "Stalemate! It's a draw!",
                                          [&] () {
                                              game = Game();
                                          },
                                          [&] () {
                                              gameUI.hide();
                                              menu.show();
                                              appState = APP_STATE::MAIN_MENU;
                                          }
                );
            }
        }
        
        gameUI.setMenuCallback([&] () {
            gameUI.hide();
            menu.show();
            appState = APP_STATE::MAIN_MENU;
        });

        gameUI.setNavigationCallbacks(
            [&]() {},
            [&]() {},
            [&]() {},
            [&]() {}
        );
        
        
        window.clear(sf::Color::Black);

        if (appState == APP_STATE::PLAYING) {
                renderer.draw(window, game.getBoard());
                if(game.isPieceSelected()) {
                    renderer.drawHighlight(window, game.getSelectedRow(), game.getSelectedCol());
                }
                if(game.isAwaitingPromotion()) {
                    renderer.drawPromoteDialog(window, game.getPromotionColor());
                }
            }
            
            gui.draw();
            
            window.display();
        }
        return 0;
    }
