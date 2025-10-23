#pragma once
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>
#include <functional>
#include "theme.h"
#include "piece.h"

enum class MENU_CHOICE {
    NONE,
    SINGLE_PLAYER,
    MULTIPLAYER,
    SETTINGS,
    QUIT
};

class Menu {
private:
    tgui::Gui& gui;
    Theme& theme;
    MENU_CHOICE choice;
    bool showing;
    ThemeType selectedThemeType;
    bool themeChanged;

    void createMainMenuView();
    void showSettingsDialog();

public:
    Menu(tgui::Gui& gui, Theme& theme);

    void show();
    void hide();
    bool isShowing() const {return showing;}

    MENU_CHOICE getChoice() const {return choice;}
    void resetChoice() {choice = MENU_CHOICE::NONE;}

    ThemeType getSelectedThemeType() const {return selectedThemeType;}
    void setThemeType(ThemeType type) {selectedThemeType = type;}
    bool hasThemeChanged() const {return themeChanged;}
    void resetThemeChanged() {themeChanged = false;}
};

class GameUI {

private:
    tgui::Gui& gui;
    Theme& theme;
    tgui::Label::Ptr turnLabel;
    tgui::Label::Ptr statusLabel;
    tgui::Button::Ptr menuButton;
    std::function<void()> onMenuPressed;

public:
    GameUI(tgui::Gui& gui, Theme& theme);

    void show();
    void hide();

    void updateTurn(const std::string& color);
    void updateStatus(const std::string& status);

    void setMenuCallback(std::function<void()> callback);
    void showGameOverDialog(const std::string& message, std::function<void()> onRestart, std::function<void()> onQuit);
    void showPromotionDialog(PIECE_COLOR color, std::function<void(PIECE_TYPE)> onSelect);
};
