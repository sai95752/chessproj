#include "theme.h"

Theme getTheme(ThemeType type) {
    switch(type) {
        case ThemeType::CLASSIC:
            return Theme(
                sf::Color(240, 217, 181),
                sf::Color(181, 136, 99),
                sf::Color(255, 255, 0, 100)
            );
            
        case ThemeType::MODERN:
            return Theme(
                sf::Color(235, 236, 208),
                sf::Color(119, 149, 86),
                sf::Color(255, 255, 100, 120)
            );
            
        case ThemeType::BLUE:
            return Theme(
                sf::Color(222, 227, 230),
                sf::Color(140, 162, 173),
                sf::Color(100, 200, 255, 120)
            );
            
        case ThemeType::DARK:
            return Theme(
                sf::Color(120, 120, 120),
                sf::Color(60, 60, 60),
                sf::Color(255, 255, 100, 120)
            );
            
        default:
            return getTheme(ThemeType::CLASSIC);
    }
}
