#include <SFML/Graphics.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>
#include <TGUI/TGUI.hpp>
#include <memory>
#include "renderer.h"
#include "board.h"
#include "theme.h"
#include "game.h"
#include "menu.h"

enum class APP_STATE {
    MAIN_MENU,
    PLAYING,
    WAITING,
    PAUSED
};

int main() {
    sf::ContextSettings settings;
    settings.antiAliasingLevel = 8;  //smoother -> 8, ass -> 1

    auto desktop = sf::VideoMode::getDesktopMode();
    unsigned int WINDOW_HEIGHT = static_cast<unsigned int>(desktop.size.y * 0.85f); // 85% of screen height
    unsigned int SQUARE_SIZE = WINDOW_HEIGHT / 8;
    unsigned int BOARD_WIDTH = SQUARE_SIZE * 8;
    unsigned int PANEL_WIDTH = static_cast<unsigned int>(BOARD_WIDTH * 0.425f); // Panel is 42.5% of board width
    unsigned int WINDOW_WIDTH = PANEL_WIDTH + BOARD_WIDTH;

    // Fixed, non-resizable window
    sf::RenderWindow window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Chess", sf::State::Windowed, settings);

    // Disable resizing by setting min and max size to same value
    window.setMinimumSize(sf::Vector2u(WINDOW_WIDTH, WINDOW_HEIGHT));
    window.setMaximumSize(sf::Vector2u(WINDOW_WIDTH, WINDOW_HEIGHT));

    window.setView(window.getDefaultView());

    Theme myTheme = getTheme(ThemeType::LIGHT);

    tgui::Gui gui(window);
    std::unique_ptr<Menu> menu = std::make_unique<Menu>(gui, myTheme);
    std::unique_ptr<GameUI> gameUI = std::make_unique<GameUI>(gui, myTheme);

    APP_STATE appState = APP_STATE::MAIN_MENU;
    menu->show();

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
            if(appState == APP_STATE::PLAYING && event->is<sf::Event::MouseButtonPressed>()) {
                auto mouseEvent = event->getIf<sf::Event::MouseButtonPressed>();
                int mouseX = mouseEvent->position.x;
                int mouseY = mouseEvent->position.y;

                if(game.isAwaitingPromotion()) {
                    continue;
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
            MENU_CHOICE choice = menu->getChoice();

            if(menu->hasThemeChanged()) {
                myTheme = getTheme(menu->getSelectedThemeType());
                renderer.refreshTheme(myTheme);
                menu->resetThemeChanged();
                gui.removeAllWidgets();
                menu = std::make_unique<Menu>(gui, myTheme);
                gameUI = std::make_unique<GameUI>(gui, myTheme);
                menu->show();
            }

            if(choice == MENU_CHOICE::SINGLE_PLAYER) {
                menu->hide();
                gameUI->show();
                appState = APP_STATE::PLAYING;
                game = Game();
                menu->resetChoice();
            } else if(choice == MENU_CHOICE::MULTIPLAYER) {
                menu->hide();
                // lobbyUI->show();
                gameUI->show();
                appState = APP_STATE::PLAYING;
                game = Game();
                menu->resetChoice();
            } else if(choice == MENU_CHOICE::QUIT) {
                window.close();
            }
        }
        
        if(appState == APP_STATE::PLAYING) {
            std::string turnColor = (game.getCurrentTurn() == PIECE_COLOR::WHITE) ? "White" : "Black";
            gameUI->updateTurn(turnColor);

            if(game.getGameState() == GAME_STATE::CHECK) {
                gameUI->updateStatus("Check!");
            } else {
                gameUI->updateStatus("");
            }

            if(game.isAwaitingPromotion()) {
                static bool promotionDialogShown = false;
                if(!promotionDialogShown) {
                    gameUI->showPromotionDialog(game.getPromotionColor(), [&](PIECE_TYPE choice) {
                        game.handlePromotion(choice);
                        promotionDialogShown = false;
                    });
                    promotionDialogShown = true;
                }
            }

            if(game.getGameState() == GAME_STATE::CHECKMATE) {
                static bool gameOverDialogShown = false;
                if(!gameOverDialogShown) {
                    std::string winner = game.getCurrentTurn() == PIECE_COLOR::WHITE ? "Black" : "White";
                    gameUI->showGameOverDialog(
                        "Checkmate! " + winner + " wins!",
                        [&] () {
                            game = Game();
                            gameOverDialogShown = false;
                        },
                        [&] () {
                            gameUI->hide();
                            menu->show();
                            appState = APP_STATE::MAIN_MENU;
                            gameOverDialogShown = false;
                        }
                    );
                    gameOverDialogShown = true;
                }
            } else if(game.getGameState() == GAME_STATE::STALEMATE) {
                static bool stalemateDialogShown = false;
                if(!stalemateDialogShown) {
                    gameUI->showGameOverDialog(
                        "Stalemate! It's a draw!",
                        [&] () {
                            game = Game();
                            stalemateDialogShown = false;
                        },
                        [&] () {
                            gameUI->hide();
                            menu->show();
                            appState = APP_STATE::MAIN_MENU;
                            stalemateDialogShown = false;
                        }
                    );
                    stalemateDialogShown = true;
                }
            }
        }

        gameUI->setMenuCallback([&] () {
            gameUI->hide();
            menu->show();
            appState = APP_STATE::MAIN_MENU;
        });

        window.clear(sf::Color::Black);

        if (appState == APP_STATE::PLAYING) {
                renderer.draw(window, game.getBoard());
                if(game.isPieceSelected()) {
                    renderer.drawHighlight(window, game.getSelectedRow(), game.getSelectedCol());
                }
            }
            
            gui.draw();
            
            window.display();
        }
        return 0;
    }
