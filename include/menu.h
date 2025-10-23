#pragma once
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>
#include <functional>
#include "theme.h"

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
    void showMessage(const std::string& title, const std::string& message);
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
    void reopenSettingsDialog() {showSettingsDialog();}
};

class GameUI {

private:
    tgui::Gui& gui;
    Theme& theme;
    tgui::Label::Ptr turnLabel;
    tgui::Label::Ptr statusLabel;
    tgui::Button::Ptr menuButton;
    tgui::ListBox::Ptr moveHistoryList;
    tgui::Button::Ptr firstMoveButton;
    tgui::Button::Ptr prevMoveButton;
    tgui::Button::Ptr nextMoveButton;
    tgui::Button::Ptr lastMoveButton;
    std::function<void()> onMenuPressed;


public:
    GameUI(tgui::Gui& gui, Theme& theme);

    void show();
    void hide();

    void updateTurn(const std::string& color);
    void updateStatus(const std::string& status);
    void addMoveToHistory(const std::string& move);
    void clearMoveHistory();

    void setMenuCallback(std::function<void()> callback);
    void setNavigationCallbacks(
        std::function<void()> onFirst,
        std::function<void()> onPrev,
        std::function<void()> onNext,
        std::function<void()> onLast
    );
    void showGameOverDialog(const std::string& message, std::function<void()> onRestart, std::function<void()> onQuit);

};


