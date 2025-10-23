#include "theme.h"

Theme getTheme(ThemeType type) {
    switch(type) {
        case ThemeType::LIGHT:
            return Theme(
                sf::Color(240, 240, 245),
                sf::Color(200, 200, 210),
                sf::Color(100, 150, 255, 120),
                sf::Color(250, 250, 255, 255),
                sf::Color(255, 255, 255, 255),
                sf::Color(100, 150, 255),
                sf::Color(20, 20, 30),
                sf::Color(100, 100, 120)
            );

        case ThemeType::DARK:
            return Theme(
                sf::Color(60, 60, 70),
                sf::Color(40, 40, 50),
                sf::Color(120, 180, 255, 100),
                sf::Color(8, 8, 10, 250),
                sf::Color(32, 32, 38, 220),
                sf::Color(200, 200, 210),
                sf::Color(245, 245, 250),
                sf::Color(160, 160, 170)
            );

        default:
            return getTheme(ThemeType::LIGHT);
    }
}
