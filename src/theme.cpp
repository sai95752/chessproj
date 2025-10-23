#include "theme.h"

namespace {
    inline int clamp(int v){ return v < 0 ? 0 : (v > 255 ? 255 : v); }
    sf::Color dull(sf::Color c, float factor){
        int target = 128;
        return sf::Color(
            static_cast<uint8_t>(clamp(static_cast<int>(c.r + (target - c.r) * factor))),
            static_cast<uint8_t>(clamp(static_cast<int>(c.g + (target - c.g) * factor))),
            static_cast<uint8_t>(clamp(static_cast<int>(c.b + (target - c.b) * factor))),
            c.a
        );
    }
}

Theme getTheme(ThemeType type) {
    const float boardDull = 0.20f;
    const float uiDull = 0.12f;
    const float buttonDull = 0.10f;
    const float textDull = 0.08f;

    switch(type) {
        case ThemeType::CLASSIC:
            return Theme(
                dull(sf::Color(240, 217, 181), boardDull),
                dull(sf::Color(181, 136, 99), boardDull),
                sf::Color(255, 255, 0, 100),
                dull(sf::Color(250, 250, 252), uiDull),
                dull(sf::Color(255, 255, 255), uiDull),
                dull(sf::Color(248, 249, 250), uiDull),
                dull(sf::Color(220, 220, 225), uiDull),
                dull(sf::Color(230, 230, 235), uiDull),
                dull(sf::Color(181, 136, 99), buttonDull),
                dull(sf::Color(161, 116, 79), buttonDull),
                dull(sf::Color(240, 240, 245), buttonDull),
                dull(sf::Color(220, 220, 225), buttonDull),
                dull(sf::Color(220, 80, 70), buttonDull),
                dull(sf::Color(200, 60, 50), buttonDull),
                dull(sf::Color(119, 149, 86), buttonDull),
                dull(sf::Color(99, 129, 66), buttonDull),
                dull(sf::Color(30, 30, 35), textDull),
                dull(sf::Color(110, 110, 120), textDull),
                dull(sf::Color(181, 136, 99), textDull),
                sf::Color(255, 255, 255)
            );

        case ThemeType::MODERN:
            return Theme(
                dull(sf::Color(235, 236, 208), boardDull),
                dull(sf::Color(119, 149, 86), boardDull),
                sf::Color(255, 255, 100, 120),
                dull(sf::Color(250, 251, 248), uiDull),
                dull(sf::Color(255, 255, 255), uiDull),
                dull(sf::Color(248, 250, 246), uiDull),
                dull(sf::Color(210, 220, 200), uiDull),
                dull(sf::Color(225, 230, 215), uiDull),
                dull(sf::Color(119, 149, 86), buttonDull),
                dull(sf::Color(99, 129, 66), buttonDull),
                dull(sf::Color(240, 242, 238), buttonDull),
                dull(sf::Color(220, 225, 210), buttonDull),
                dull(sf::Color(200, 80, 70), buttonDull),
                dull(sf::Color(180, 60, 50), buttonDull),
                dull(sf::Color(100, 180, 100), buttonDull),
                dull(sf::Color(80, 160, 80), buttonDull),
                dull(sf::Color(30, 35, 30), textDull),
                dull(sf::Color(100, 115, 90), textDull),
                dull(sf::Color(119, 149, 86), textDull),
                sf::Color(255, 255, 255)
            );

        case ThemeType::BLUE:
            return Theme(
                dull(sf::Color(222, 227, 230), boardDull),
                dull(sf::Color(140, 162, 173), boardDull),
                sf::Color(100, 200, 255, 120),
                dull(sf::Color(245, 248, 250), uiDull),
                dull(sf::Color(255, 255, 255), uiDull),
                dull(sf::Color(248, 251, 253), uiDull),
                dull(sf::Color(200, 215, 225), uiDull),
                dull(sf::Color(220, 230, 238), uiDull),
                dull(sf::Color(70, 130, 180), buttonDull),
                dull(sf::Color(50, 110, 160), buttonDull),
                dull(sf::Color(240, 245, 248), buttonDull),
                dull(sf::Color(220, 230, 238), buttonDull),
                dull(sf::Color(210, 70, 80), buttonDull),
                dull(sf::Color(190, 50, 60), buttonDull),
                dull(sf::Color(80, 160, 120), buttonDull),
                dull(sf::Color(60, 140, 100), buttonDull),
                dull(sf::Color(25, 35, 45), textDull),
                dull(sf::Color(100, 115, 130), textDull),
                dull(sf::Color(70, 130, 180), textDull),
                sf::Color(255, 255, 255)
            );

        case ThemeType::DARK:
            return Theme(
                dull(sf::Color(120, 120, 120), boardDull),
                dull(sf::Color(60, 60, 60), boardDull),
                sf::Color(255, 255, 100, 120),
                dull(sf::Color(18, 18, 20), uiDull),
                dull(sf::Color(30, 30, 35), uiDull),
                dull(sf::Color(40, 40, 45), uiDull),
                dull(sf::Color(55, 55, 60), uiDull),
                dull(sf::Color(45, 45, 50), uiDull),
                dull(sf::Color(70, 130, 180), buttonDull),
                dull(sf::Color(90, 150, 200), buttonDull),
                dull(sf::Color(50, 50, 60), buttonDull),
                dull(sf::Color(65, 65, 75), buttonDull),
                dull(sf::Color(200, 70, 70), buttonDull),
                dull(sf::Color(220, 90, 90), buttonDull),
                dull(sf::Color(80, 180, 120), buttonDull),
                dull(sf::Color(100, 200, 140), buttonDull),
                dull(sf::Color(230, 230, 235), textDull),
                dull(sf::Color(140, 140, 150), textDull),
                dull(sf::Color(120, 180, 230), textDull),
                sf::Color(255, 255, 255)
            );

        case ThemeType::NEON_CYBERPUNK:
            return Theme(
                dull(sf::Color(20, 20, 40), boardDull),
                dull(sf::Color(10, 10, 25), boardDull),
                sf::Color(255, 0, 255, 150),
                dull(sf::Color(5, 5, 15), uiDull),
                dull(sf::Color(15, 15, 30), uiDull),
                dull(sf::Color(25, 25, 40), uiDull),
                dull(sf::Color(100, 50, 150), uiDull),
                dull(sf::Color(50, 150, 150), uiDull),
                dull(sf::Color(200, 50, 200), buttonDull),
                dull(sf::Color(180, 30, 180), buttonDull),
                dull(sf::Color(30, 30, 50), buttonDull),
                dull(sf::Color(40, 40, 60), buttonDull),
                dull(sf::Color(255, 50, 100), buttonDull),
                dull(sf::Color(200, 30, 80), buttonDull),
                dull(sf::Color(50, 200, 180), buttonDull),
                dull(sf::Color(30, 180, 160), buttonDull),
                dull(sf::Color(100, 200, 200), textDull),
                dull(sf::Color(200, 100, 200), textDull),
                dull(sf::Color(180, 180, 100), textDull),
                sf::Color(255, 255, 255)
            );

        case ThemeType::SAKURA:
            return Theme(
                dull(sf::Color(255, 240, 245), boardDull),
                dull(sf::Color(255, 182, 193), boardDull),
                sf::Color(255, 105, 180, 100),
                dull(sf::Color(255, 250, 252), uiDull),
                dull(sf::Color(255, 255, 255), uiDull),
                dull(sf::Color(255, 245, 250), uiDull),
                dull(sf::Color(255, 182, 193), uiDull),
                dull(sf::Color(255, 218, 224), uiDull),
                dull(sf::Color(219, 112, 147), buttonDull),
                dull(sf::Color(199, 92, 127), buttonDull),
                dull(sf::Color(255, 240, 245), buttonDull),
                dull(sf::Color(255, 220, 230), buttonDull),
                dull(sf::Color(220, 80, 100), buttonDull),
                dull(sf::Color(200, 60, 80), buttonDull),
                dull(sf::Color(255, 182, 193), buttonDull),
                dull(sf::Color(235, 162, 173), buttonDull),
                dull(sf::Color(139, 69, 94), textDull),
                dull(sf::Color(219, 112, 147), textDull),
                dull(sf::Color(255, 105, 180), textDull),
                sf::Color(255, 255, 255)
            );

        case ThemeType::FOREST:
            return Theme(
                dull(sf::Color(193, 225, 193), boardDull),
                dull(sf::Color(76, 128, 76), boardDull),
                sf::Color(144, 238, 144, 120),
                dull(sf::Color(245, 252, 245), uiDull),
                dull(sf::Color(255, 255, 255), uiDull),
                dull(sf::Color(248, 254, 248), uiDull),
                dull(sf::Color(144, 180, 144), uiDull),
                dull(sf::Color(193, 225, 193), uiDull),
                dull(sf::Color(60, 130, 60), buttonDull),
                dull(sf::Color(50, 110, 50), buttonDull),
                dull(sf::Color(240, 248, 240), buttonDull),
                dull(sf::Color(220, 235, 220), buttonDull),
                dull(sf::Color(178, 80, 80), buttonDull),
                dull(sf::Color(158, 60, 60), buttonDull),
                dull(sf::Color(100, 200, 100), buttonDull),
                dull(sf::Color(80, 180, 80), buttonDull),
                dull(sf::Color(40, 70, 40), textDull),
                dull(sf::Color(76, 128, 76), textDull),
                dull(sf::Color(60, 130, 60), textDull),
                sf::Color(255, 255, 255)
            );

        case ThemeType::SUNSET:
            return Theme(
                dull(sf::Color(255, 218, 185), boardDull),
                dull(sf::Color(255, 127, 80), boardDull),
                sf::Color(255, 215, 0, 120),
                dull(sf::Color(255, 250, 240), uiDull),
                dull(sf::Color(255, 255, 255), uiDull),
                dull(sf::Color(255, 248, 238), uiDull),
                dull(sf::Color(255, 160, 122), uiDull),
                dull(sf::Color(255, 200, 150), uiDull),
                dull(sf::Color(230, 110, 80), buttonDull),
                dull(sf::Color(210, 90, 60), buttonDull),
                dull(sf::Color(255, 235, 205), buttonDull),
                dull(sf::Color(255, 215, 185), buttonDull),
                dull(sf::Color(220, 80, 60), buttonDull),
                dull(sf::Color(200, 60, 40), buttonDull),
                dull(sf::Color(255, 150, 50), buttonDull),
                dull(sf::Color(235, 130, 30), buttonDull),
                dull(sf::Color(120, 80, 40), textDull),
                dull(sf::Color(180, 120, 70), textDull),
                dull(sf::Color(230, 100, 50), textDull),
                sf::Color(255, 255, 255)
            );

        case ThemeType::OCEAN_DEEP:
            return Theme(
                dull(sf::Color(176, 224, 230), boardDull),
                dull(sf::Color(50, 120, 150), boardDull),
                sf::Color(64, 224, 208, 120),
                dull(sf::Color(230, 245, 250), uiDull),
                dull(sf::Color(255, 255, 255), uiDull),
                dull(sf::Color(240, 248, 255), uiDull),
                dull(sf::Color(100, 149, 200), uiDull),
                dull(sf::Color(150, 180, 210), uiDull),
                dull(sf::Color(50, 130, 180), buttonDull),
                dull(sf::Color(40, 110, 160), buttonDull),
                dull(sf::Color(230, 242, 255), buttonDull),
                dull(sf::Color(210, 230, 250), buttonDull),
                dull(sf::Color(180, 60, 80), buttonDull),
                dull(sf::Color(160, 40, 60), buttonDull),
                dull(sf::Color(80, 180, 170), buttonDull),
                dull(sf::Color(60, 160, 150), buttonDull),
                dull(sf::Color(30, 60, 90), textDull),
                dull(sf::Color(70, 130, 180), textDull),
                dull(sf::Color(50, 140, 200), textDull),
                sf::Color(255, 255, 255)
            );

        case ThemeType::LAVA:
            return Theme(
                dull(sf::Color(70, 70, 70), boardDull),
                dull(sf::Color(40, 40, 40), boardDull),
                sf::Color(255, 100, 50, 150),
                dull(sf::Color(30, 30, 30), uiDull),
                dull(sf::Color(40, 40, 40), uiDull),
                dull(sf::Color(50, 50, 50), uiDull),
                dull(sf::Color(180, 80, 30), uiDull),
                dull(sf::Color(120, 80, 50), uiDull),
                dull(sf::Color(200, 80, 30), buttonDull),
                dull(sf::Color(180, 60, 20), buttonDull),
                dull(sf::Color(60, 60, 60), buttonDull),
                dull(sf::Color(75, 75, 75), buttonDull),
                dull(sf::Color(180, 60, 60), buttonDull),
                dull(sf::Color(160, 40, 40), buttonDull),
                dull(sf::Color(220, 120, 50), buttonDull),
                dull(sf::Color(200, 100, 30), buttonDull),
                dull(sf::Color(200, 200, 180), textDull),
                dull(sf::Color(220, 150, 80), textDull),
                dull(sf::Color(230, 120, 70), textDull),
                sf::Color(255, 255, 255)
            );

        case ThemeType::ICE_PALACE:
            return Theme(
                dull(sf::Color(240, 248, 255), boardDull),
                dull(sf::Color(176, 224, 230), boardDull),
                sf::Color(173, 216, 230, 120),
                dull(sf::Color(245, 255, 255), uiDull),
                dull(sf::Color(255, 255, 255), uiDull),
                dull(sf::Color(248, 252, 255), uiDull),
                dull(sf::Color(135, 206, 235), uiDull),
                dull(sf::Color(176, 224, 230), uiDull),
                dull(sf::Color(100, 149, 237), buttonDull),
                dull(sf::Color(80, 130, 220), buttonDull),
                dull(sf::Color(240, 248, 255), buttonDull),
                dull(sf::Color(220, 235, 255), buttonDull),
                dull(sf::Color(160, 80, 200), buttonDull),
                dull(sf::Color(140, 60, 180), buttonDull),
                dull(sf::Color(135, 206, 250), buttonDull),
                dull(sf::Color(115, 186, 230), buttonDull),
                dull(sf::Color(40, 50, 100), textDull),
                dull(sf::Color(100, 149, 237), textDull),
                dull(sf::Color(80, 130, 210), textDull),
                sf::Color(255, 255, 255)
            );

        case ThemeType::RETRO_ARCADE:
            return Theme(
                dull(sf::Color(200, 200, 120), boardDull),
                dull(sf::Color(200, 120, 200), boardDull),
                sf::Color(100, 200, 200, 150),
                dull(sf::Color(10, 10, 10), uiDull),
                dull(sf::Color(25, 25, 40), uiDull),
                dull(sf::Color(35, 35, 50), uiDull),
                dull(sf::Color(180, 50, 180), uiDull),
                dull(sf::Color(50, 180, 180), uiDull),
                dull(sf::Color(200, 50, 150), buttonDull),
                dull(sf::Color(180, 40, 130), buttonDull),
                dull(sf::Color(40, 40, 60), buttonDull),
                dull(sf::Color(55, 55, 75), buttonDull),
                dull(sf::Color(220, 80, 80), buttonDull),
                dull(sf::Color(200, 60, 60), buttonDull),
                dull(sf::Color(80, 200, 150), buttonDull),
                dull(sf::Color(60, 180, 130), buttonDull),
                dull(sf::Color(200, 200, 200), textDull),
                dull(sf::Color(100, 200, 200), textDull),
                dull(sf::Color(200, 200, 100), textDull),
                sf::Color(255, 255, 255)
            );

        case ThemeType::LAVENDER_DREAM:
            return Theme(
                dull(sf::Color(243, 229, 245), boardDull),
                dull(sf::Color(216, 191, 216), boardDull),
                sf::Color(221, 160, 221, 120),
                dull(sf::Color(250, 245, 252), uiDull),
                dull(sf::Color(255, 255, 255), uiDull),
                dull(sf::Color(248, 243, 250), uiDull),
                dull(sf::Color(216, 191, 216), uiDull),
                dull(sf::Color(230, 210, 235), uiDull),
                dull(sf::Color(147, 112, 219), buttonDull),
                dull(sf::Color(127, 92, 199), buttonDull),
                dull(sf::Color(245, 235, 250), buttonDull),
                dull(sf::Color(230, 215, 240), buttonDull),
                dull(sf::Color(180, 60, 140), buttonDull),
                dull(sf::Color(160, 40, 120), buttonDull),
                dull(sf::Color(186, 120, 200), buttonDull),
                dull(sf::Color(166, 100, 180), buttonDull),
                dull(sf::Color(90, 40, 120), textDull),
                dull(sf::Color(147, 112, 219), textDull),
                dull(sf::Color(150, 90, 200), textDull),
                sf::Color(255, 255, 255)
            );

        case ThemeType::DESERT_SAND:
            return Theme(
                dull(sf::Color(244, 228, 188), boardDull),
                dull(sf::Color(210, 180, 140), boardDull),
                sf::Color(255, 215, 0, 100),
                dull(sf::Color(250, 240, 220), uiDull),
                dull(sf::Color(255, 255, 255), uiDull),
                dull(sf::Color(252, 245, 230), uiDull),
                dull(sf::Color(205, 175, 135), uiDull),
                dull(sf::Color(222, 200, 170), uiDull),
                dull(sf::Color(170, 130, 60), buttonDull),
                dull(sf::Color(150, 110, 40), buttonDull),
                dull(sf::Color(245, 235, 215), buttonDull),
                dull(sf::Color(230, 220, 200), buttonDull),
                dull(sf::Color(180, 70, 70), buttonDull),
                dull(sf::Color(160, 50, 50), buttonDull),
                dull(sf::Color(180, 170, 110), buttonDull),
                dull(sf::Color(160, 150, 90), buttonDull),
                dull(sf::Color(110, 80, 50), textDull),
                dull(sf::Color(139, 100, 60), textDull),
                dull(sf::Color(170, 130, 50), textDull),
                sf::Color(255, 255, 255)
            );

        case ThemeType::MINT_CHOCOLATE:
            return Theme(
                dull(sf::Color(245, 255, 250), boardDull),
                dull(sf::Color(152, 220, 180), boardDull),
                sf::Color(150, 220, 180, 120),
                dull(sf::Color(248, 255, 252), uiDull),
                dull(sf::Color(255, 255, 255), uiDull),
                dull(sf::Color(250, 255, 253), uiDull),
                dull(sf::Color(152, 220, 180), uiDull),
                dull(sf::Color(180, 230, 200), uiDull),
                dull(sf::Color(80, 180, 160), buttonDull),
                dull(sf::Color(60, 160, 140), buttonDull),
                dull(sf::Color(245, 255, 250), buttonDull),
                dull(sf::Color(230, 250, 240), buttonDull),
                dull(sf::Color(180, 60, 130), buttonDull),
                dull(sf::Color(160, 40, 110), buttonDull),
                dull(sf::Color(120, 200, 150), buttonDull),
                dull(sf::Color(100, 180, 130), buttonDull),
                dull(sf::Color(60, 90, 80), textDull),
                dull(sf::Color(80, 160, 120), textDull),
                dull(sf::Color(80, 180, 150), textDull),
                sf::Color(255, 255, 255)
            );

        case ThemeType::VAMPIRE:
            return Theme(
                dull(sf::Color(80, 50, 50), boardDull),
                dull(sf::Color(50, 30, 30), boardDull),
                sf::Color(150, 50, 50, 150),
                dull(sf::Color(20, 15, 15), uiDull),
                dull(sf::Color(35, 25, 25), uiDull),
                dull(sf::Color(50, 35, 35), uiDull),
                dull(sf::Color(120, 40, 40), uiDull),
                dull(sf::Color(80, 40, 40), uiDull),
                dull(sf::Color(130, 40, 40), buttonDull),
                dull(sf::Color(110, 30, 30), buttonDull),
                dull(sf::Color(60, 40, 40), buttonDull),
                dull(sf::Color(75, 50, 50), buttonDull),
                dull(sf::Color(180, 60, 80), buttonDull),
                dull(sf::Color(160, 40, 60), buttonDull),
                dull(sf::Color(150, 70, 70), buttonDull),
                dull(sf::Color(130, 50, 50), buttonDull),
                dull(sf::Color(200, 180, 180), textDull),
                dull(sf::Color(180, 120, 120), textDull),
                dull(sf::Color(180, 80, 100), textDull),
                sf::Color(255, 255, 255)
            );

        case ThemeType::GOLD_RUSH:
            return Theme(
                dull(sf::Color(255, 248, 220), boardDull),
                dull(sf::Color(218, 165, 80), boardDull),
                sf::Color(230, 190, 50, 120),
                dull(sf::Color(255, 253, 240), uiDull),
                dull(sf::Color(255, 255, 255), uiDull),
                dull(sf::Color(255, 250, 235), uiDull),
                dull(sf::Color(218, 165, 80), uiDull),
                dull(sf::Color(230, 185, 110), uiDull),
                dull(sf::Color(180, 140, 50), buttonDull),
                dull(sf::Color(160, 120, 30), buttonDull),
                dull(sf::Color(255, 250, 205), buttonDull),
                dull(sf::Color(245, 230, 180), buttonDull),
                dull(sf::Color(180, 70, 70), buttonDull),
                dull(sf::Color(160, 50, 50), buttonDull),
                dull(sf::Color(230, 190, 50), buttonDull),
                dull(sf::Color(210, 170, 30), buttonDull),
                dull(sf::Color(110, 80, 40), textDull),
                dull(sf::Color(170, 130, 50), textDull),
                dull(sf::Color(200, 155, 60), textDull),
                sf::Color(255, 255, 255)
            );

        case ThemeType::AURORA:
            return Theme(
                dull(sf::Color(230, 255, 250), boardDull),
                dull(sf::Color(152, 230, 200), boardDull),
                sf::Color(127, 230, 200, 120),
                dull(sf::Color(240, 255, 252), uiDull),
                dull(sf::Color(255, 255, 255), uiDull),
                dull(sf::Color(245, 255, 253), uiDull),
                dull(sf::Color(150, 220, 200), uiDull),
                dull(sf::Color(175, 235, 215), uiDull),
                dull(sf::Color(80, 200, 180), buttonDull),
                dull(sf::Color(60, 180, 160), buttonDull),
                dull(sf::Color(240, 255, 250), buttonDull),
                dull(sf::Color(220, 245, 235), buttonDull),
                dull(sf::Color(200, 70, 130), buttonDull),
                dull(sf::Color(180, 50, 110), buttonDull),
                dull(sf::Color(100, 220, 150), buttonDull),
                dull(sf::Color(80, 200, 130), buttonDull),
                dull(sf::Color(40, 100, 100), textDull),
                dull(sf::Color(80, 200, 180), textDull),
                dull(sf::Color(90, 190, 175), textDull),
                sf::Color(255, 255, 255)
            );

        case ThemeType::NOIR:
            return Theme(
                dull(sf::Color(100, 100, 100), boardDull),
                dull(sf::Color(55, 55, 55), boardDull),
                sf::Color(180, 180, 180, 100),
                dull(sf::Color(25, 25, 25), uiDull),
                dull(sf::Color(40, 40, 40), uiDull),
                dull(sf::Color(55, 55, 55), uiDull),
                dull(sf::Color(100, 100, 100), uiDull),
                dull(sf::Color(70, 70, 70), uiDull),
                dull(sf::Color(130, 130, 130), buttonDull),
                dull(sf::Color(110, 110, 110), buttonDull),
                dull(sf::Color(60, 60, 60), buttonDull),
                dull(sf::Color(80, 80, 80), buttonDull),
                dull(sf::Color(160, 160, 160), buttonDull),
                dull(sf::Color(140, 140, 140), buttonDull),
                dull(sf::Color(180, 180, 180), buttonDull),
                dull(sf::Color(160, 160, 160), buttonDull),
                dull(sf::Color(200, 200, 200), textDull),
                dull(sf::Color(140, 140, 140), textDull),
                dull(sf::Color(180, 180, 180), textDull),
                sf::Color(255, 255, 255)
            );

        case ThemeType::BUBBLEGUM:
            return Theme(
                dull(sf::Color(255, 240, 245), boardDull),
                dull(sf::Color(255, 192, 203), boardDull),
                sf::Color(255, 150, 200, 120),
                dull(sf::Color(255, 250, 252), uiDull),
                dull(sf::Color(255, 255, 255), uiDull),
                dull(sf::Color(255, 245, 250), uiDull),
                dull(sf::Color(255, 182, 193), uiDull),
                dull(sf::Color(255, 218, 224), uiDull),
                dull(sf::Color(230, 80, 150), buttonDull),
                dull(sf::Color(210, 60, 130), buttonDull),
                dull(sf::Color(255, 240, 245), buttonDull),
                dull(sf::Color(255, 220, 230), buttonDull),
                dull(sf::Color(200, 60, 90), buttonDull),
                dull(sf::Color(180, 40, 70), buttonDull),
                dull(sf::Color(255, 182, 193), buttonDull),
                dull(sf::Color(235, 162, 173), buttonDull),
                dull(sf::Color(160, 60, 110), textDull),
                dull(sf::Color(220, 120, 160), textDull),
                dull(sf::Color(230, 80, 140), textDull),
                sf::Color(255, 255, 255)
            );

        case ThemeType::TOXIC:
            return Theme(
                dull(sf::Color(180, 220, 100), boardDull),
                dull(sf::Color(80, 180, 80), boardDull),
                sf::Color(100, 200, 100, 150),
                dull(sf::Color(25, 35, 25), uiDull),
                dull(sf::Color(35, 45, 35), uiDull),
                dull(sf::Color(45, 55, 45), uiDull),
                dull(sf::Color(80, 180, 80), uiDull),
                dull(sf::Color(80, 170, 80), uiDull),
                dull(sf::Color(80, 200, 80), buttonDull),
                dull(sf::Color(60, 180, 60), buttonDull),
                dull(sf::Color(45, 55, 45), buttonDull),
                dull(sf::Color(60, 70, 60), buttonDull),
                dull(sf::Color(200, 80, 80), buttonDull),
                dull(sf::Color(180, 60, 60), buttonDull),
                dull(sf::Color(80, 180, 80), buttonDull),
                dull(sf::Color(60, 160, 60), buttonDull),
                dull(sf::Color(150, 200, 100), textDull),
                dull(sf::Color(120, 200, 80), textDull),
                dull(sf::Color(100, 200, 100), textDull),
                sf::Color(220, 255, 220)
            );

        case ThemeType::ROYAL_PURPLE:
            return Theme(
                dull(sf::Color(230, 220, 240), boardDull),
                dull(sf::Color(147, 112, 180), boardDull),
                sf::Color(150, 100, 200, 120),
                dull(sf::Color(245, 240, 250), uiDull),
                dull(sf::Color(255, 255, 255), uiDull),
                dull(sf::Color(250, 245, 255), uiDull),
                dull(sf::Color(147, 112, 180), uiDull),
                dull(sf::Color(180, 160, 210), uiDull),
                dull(sf::Color(100, 50, 150), buttonDull),
                dull(sf::Color(80, 40, 130), buttonDull),
                dull(sf::Color(240, 230, 250), buttonDull),
                dull(sf::Color(225, 210, 240), buttonDull),
                dull(sf::Color(180, 60, 140), buttonDull),
                dull(sf::Color(160, 40, 120), buttonDull),
                dull(sf::Color(150, 90, 200), buttonDull),
                dull(sf::Color(130, 70, 180), buttonDull),
                dull(sf::Color(70, 40, 90), textDull),
                dull(sf::Color(120, 80, 160), textDull),
                dull(sf::Color(140, 90, 200), textDull),
                sf::Color(255, 255, 255)
            );

        case ThemeType::MATRIX:
            return Theme(
                dull(sf::Color(20, 60, 20), boardDull),
                dull(sf::Color(10, 35, 10), boardDull),
                sf::Color(50, 200, 50, 150),
                dull(sf::Color(5, 5, 5), uiDull),
                dull(sf::Color(10, 20, 10), uiDull),
                dull(sf::Color(15, 30, 15), uiDull),
                dull(sf::Color(50, 180, 50), uiDull),
                dull(sf::Color(40, 130, 40), uiDull),
                dull(sf::Color(50, 200, 50), buttonDull),
                dull(sf::Color(40, 180, 40), buttonDull),
                dull(sf::Color(15, 35, 15), buttonDull),
                dull(sf::Color(20, 50, 20), buttonDull),
                dull(sf::Color(200, 50, 50), buttonDull),
                dull(sf::Color(180, 40, 40), buttonDull),
                dull(sf::Color(50, 180, 50), buttonDull),
                dull(sf::Color(40, 160, 40), buttonDull),
                dull(sf::Color(80, 200, 80), textDull),
                dull(sf::Color(50, 180, 50), textDull),
                dull(sf::Color(60, 200, 90), textDull),
                sf::Color(100, 255, 100)
            );

        default:
            return getTheme(ThemeType::CLASSIC);
    }
}
