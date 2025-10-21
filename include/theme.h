#pragma once
#include <SFML/Graphics.hpp>

//TODO
//ADD FONT and DIALOG theming into struct
struct Theme {
private:
    sf::Color LIGHT_COLOR;
    sf::Color DARK_COLOR;
    sf::Color HIGHLIGHT_COLOR;
public:
    Theme(sf::Color LIGHT_COLOR, sf::Color DARK_COLOR, sf::Color HIGHLIGHT_COLOR) {
        this->LIGHT_COLOR = LIGHT_COLOR;
        this->DARK_COLOR = DARK_COLOR;
        this->HIGHLIGHT_COLOR = HIGHLIGHT_COLOR;
    }
    sf::Color getLc() {
        return this->LIGHT_COLOR;
    }
    sf::Color getDc() {
        return this->DARK_COLOR;
    }
    sf::Color getHc() {
        return this->HIGHLIGHT_COLOR;
    }
};

enum class ThemeType {
    CLASSIC,
    MODERN,
    BLUE,
    DARK
};

Theme getTheme(ThemeType type);
