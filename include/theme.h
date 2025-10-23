#pragma once
#include <SFML/Graphics.hpp>

enum class ThemeType {
    LIGHT,
    DARK
};

struct Theme {
private:
    sf::Color LIGHT_COLOR, DARK_COLOR, HIGHLIGHT_COLOR;
    sf::Color UI_BACKGROUND, UI_PANEL, UI_ACCENT;
    sf::Color TEXT_PRIMARY, TEXT_SECONDARY;

public:
    Theme(
        sf::Color light, sf::Color dark, sf::Color highlight,
        sf::Color uiBg, sf::Color uiPanel, sf::Color uiAccent,
        sf::Color textPrimary, sf::Color textSecondary
    ) : LIGHT_COLOR(light), DARK_COLOR(dark), HIGHLIGHT_COLOR(highlight),
        UI_BACKGROUND(uiBg), UI_PANEL(uiPanel), UI_ACCENT(uiAccent),
        TEXT_PRIMARY(textPrimary), TEXT_SECONDARY(textSecondary) {}

    sf::Color getLc() const { return LIGHT_COLOR; }
    sf::Color getDc() const { return DARK_COLOR; }
    sf::Color getHc() const { return HIGHLIGHT_COLOR; }
    sf::Color getUiBg() const { return UI_BACKGROUND; }
    sf::Color getUiPanel() const { return UI_PANEL; }
    sf::Color getUiAccent() const { return UI_ACCENT; }
    sf::Color getTextPrimary() const { return TEXT_PRIMARY; }
    sf::Color getTextSecondary() const { return TEXT_SECONDARY; }
};

Theme getTheme(ThemeType type);
