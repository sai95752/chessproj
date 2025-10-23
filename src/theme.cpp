#include "theme.h"

Theme getTheme(ThemeType type) {
    switch(type) {
        case ThemeType::CLASSIC:
            return Theme(
                //board
                sf::Color(240, 217, 181),      // Light square
                sf::Color(181, 136, 99),       // Dark square
                sf::Color(255, 255, 0, 100),   // Highlight
                //ui
                sf::Color(250, 250, 252),      // Background
                sf::Color(255, 255, 255),      // Panel
                sf::Color(248, 249, 250),      // Panel light
                sf::Color(220, 220, 225),      // Border
                sf::Color(230, 230, 235),      // Divider
                //buttons
                sf::Color(181, 136, 99),       // Primary
                sf::Color(161, 116, 79),       // Primary hover
                sf::Color(240, 240, 245),      // Secondary
                sf::Color(220, 220, 225),      // Secondary hover
                sf::Color(220, 80, 70),        // Danger
                sf::Color(200, 60, 50),        // Danger hover
                sf::Color(119, 149, 86),       // Success
                sf::Color(99, 129, 66),        // Success hover
                //text
                sf::Color(30, 30, 35),         // Primary text
                sf::Color(110, 110, 120),      // Secondary text
                sf::Color(181, 136, 99),       // Accent text
                sf::Color(255, 255, 255)       // Text on dark
            );

        case ThemeType::MODERN:
            return Theme(
                sf::Color(235, 236, 208),      // Light square
                sf::Color(119, 149, 86),       // Dark square
                sf::Color(255, 255, 100, 120), // Highlight
                sf::Color(250, 251, 248),      // Background
                sf::Color(255, 255, 255),      // Panel
                sf::Color(248, 250, 246),      // Panel light
                sf::Color(210, 220, 200),      // Border
                sf::Color(225, 230, 215),      // Divider
                sf::Color(119, 149, 86),       // Primary
                sf::Color(99, 129, 66),        // Primary hover
                sf::Color(240, 242, 238),      // Secondary
                sf::Color(220, 225, 210),      // Secondary hover
                sf::Color(200, 80, 70),        // Danger
                sf::Color(180, 60, 50),        // Danger hover
                sf::Color(100, 180, 100),      // Success
                sf::Color(80, 160, 80),        // Success hover
                sf::Color(30, 35, 30),         // Primary text
                sf::Color(100, 115, 90),       // Secondary text
                sf::Color(119, 149, 86),       // Accent text
                sf::Color(255, 255, 255)       // Text on dark
            );

        case ThemeType::BLUE:
            return Theme(
                // Board
                sf::Color(222, 227, 230),      // Light square
                sf::Color(140, 162, 173),      // Dark square
                sf::Color(100, 200, 255, 120), // Highlight
                sf::Color(245, 248, 250),      // Background
                sf::Color(255, 255, 255),      // Panel
                sf::Color(248, 251, 253),      // Panel light
                sf::Color(200, 215, 225),      // Border
                sf::Color(220, 230, 238),      // Divider
                sf::Color(70, 130, 180),       // Primary
                sf::Color(50, 110, 160),       // Primary hover
                sf::Color(240, 245, 248),      // Secondary
                sf::Color(220, 230, 238),      // Secondary hover
                sf::Color(210, 70, 80),        // Danger
                sf::Color(190, 50, 60),        // Danger hover
                sf::Color(80, 160, 120),       // Success
                sf::Color(60, 140, 100),       // Success hover
                sf::Color(25, 35, 45),         // Primary text
                sf::Color(100, 115, 130),      // Secondary text
                sf::Color(70, 130, 180),       // Accent text
                sf::Color(255, 255, 255)       // Text on dark
            );

        case ThemeType::DARK:
            return Theme(
                sf::Color(120, 120, 120),      // Light square
                sf::Color(60, 60, 60),         // Dark square
                sf::Color(255, 255, 100, 120), // Highlight
                sf::Color(18, 18, 20),         // Background
                sf::Color(30, 30, 35),         // Panel
                sf::Color(40, 40, 45),         // Panel light
                sf::Color(55, 55, 60),         // Border
                sf::Color(45, 45, 50),         // Divider
                sf::Color(70, 130, 180),       // Primary
                sf::Color(90, 150, 200),       // Primary hover
                sf::Color(50, 50, 60),         // Secondary
                sf::Color(65, 65, 75),         // Secondary hover
                sf::Color(200, 70, 70),        // Danger
                sf::Color(220, 90, 90),        // Danger hover
                sf::Color(80, 180, 120),       // Success
                sf::Color(100, 200, 140),      // Success hover
                sf::Color(230, 230, 235),      // Primary text
                sf::Color(140, 140, 150),      // Secondary text
                sf::Color(120, 180, 230),      // Accent text
                sf::Color(255, 255, 255)       // Text on dark
            );

        case ThemeType::NEON_CYBERPUNK:
            return Theme(
                sf::Color(20, 20, 40),         // Light square
                sf::Color(10, 10, 25),         // Dark square
                sf::Color(255, 0, 255, 150),   // Highlight
                sf::Color(5, 5, 15),           // Background
                sf::Color(15, 15, 30),         // Panel
                sf::Color(25, 25, 40),         // Panel light
                sf::Color(255, 0, 255),        // Border
                sf::Color(0, 255, 255),        // Divider
                sf::Color(255, 0, 255),        // Primary
                sf::Color(200, 0, 200),        // Primary hover
                sf::Color(30, 30, 50),         // Secondary
                sf::Color(40, 40, 60),         // Secondary hover
                sf::Color(255, 50, 100),       // Danger
                sf::Color(200, 30, 80),        // Danger hover
                sf::Color(0, 255, 200),        // Success
                sf::Color(0, 200, 160),        // Success hover
                sf::Color(0, 255, 255),        // Primary text
                sf::Color(255, 0, 255),        // Secondary text
                sf::Color(255, 255, 0),        // Accent text
                sf::Color(255, 255, 255)       // Text on dark
            );

        case ThemeType::SAKURA:
            return Theme(
                sf::Color(255, 240, 245),      // Light square
                sf::Color(255, 182, 193),      // Dark square
                sf::Color(255, 105, 180, 100), // Highlight
                sf::Color(255, 250, 252),      // Background
                sf::Color(255, 255, 255),      // Panel
                sf::Color(255, 245, 250),      // Panel light
                sf::Color(255, 182, 193),      // Border
                sf::Color(255, 218, 224),      // Divider
                sf::Color(219, 112, 147),      // Primary
                sf::Color(199, 92, 127),       // Primary hover
                sf::Color(255, 240, 245),      // Secondary
                sf::Color(255, 220, 230),      // Secondary hover
                sf::Color(220, 80, 100),       // Danger
                sf::Color(200, 60, 80),        // Danger hover
                sf::Color(255, 182, 193),      // Success
                sf::Color(235, 162, 173),      // Success hover
                sf::Color(139, 69, 94),        // Primary text
                sf::Color(219, 112, 147),      // Secondary text
                sf::Color(255, 105, 180),      // Accent text
                sf::Color(255, 255, 255)       // Text on dark
            );

        case ThemeType::FOREST:
            return Theme(
                sf::Color(193, 225, 193),      // Light square
                sf::Color(76, 128, 76),        // Dark square
                sf::Color(144, 238, 144, 120), // Highlight
                sf::Color(245, 252, 245),      // Background
                sf::Color(255, 255, 255),      // Panel
                sf::Color(248, 254, 248),      // Panel light
                sf::Color(144, 180, 144),      // Border
                sf::Color(193, 225, 193),      // Divider
                sf::Color(34, 139, 34),        // Primary
                sf::Color(20, 119, 20),        // Primary hover
                sf::Color(240, 248, 240),      // Secondary
                sf::Color(220, 235, 220),      // Secondary hover
                sf::Color(178, 34, 34),        // Danger
                sf::Color(158, 20, 20),        // Danger hover
                sf::Color(144, 238, 144),      // Success
                sf::Color(124, 218, 124),      // Success hover
                sf::Color(25, 60, 25),         // Primary text
                sf::Color(76, 128, 76),        // Secondary text
                sf::Color(34, 139, 34),        // Accent text
                sf::Color(255, 255, 255)       // Text on dark
            );

        case ThemeType::SUNSET:
            return Theme(
                sf::Color(255, 218, 185),      // Light square
                sf::Color(255, 127, 80),       // Dark square
                sf::Color(255, 215, 0, 120),   // Highlight
                sf::Color(255, 250, 240),      // Background
                sf::Color(255, 255, 255),      // Panel
                sf::Color(255, 248, 238),      // Panel light
                sf::Color(255, 160, 122),      // Border
                sf::Color(255, 200, 150),      // Divider
                sf::Color(255, 99, 71),        // Primary
                sf::Color(230, 79, 51),        // Primary hover
                sf::Color(255, 235, 205),      // Secondary
                sf::Color(255, 215, 185),      // Secondary hover
                sf::Color(220, 60, 40),        // Danger
                sf::Color(200, 40, 20),        // Danger hover
                sf::Color(255, 165, 0),        // Success
                sf::Color(235, 145, 0),        // Success hover
                sf::Color(139, 69, 19),        // Primary text
                sf::Color(205, 133, 63),       // Secondary text
                sf::Color(255, 69, 0),         // Accent text
                sf::Color(255, 255, 255)       // Text on dark
            );

        case ThemeType::OCEAN_DEEP:
            return Theme(
                sf::Color(176, 224, 230),      // Light square
                sf::Color(0, 105, 148),        // Dark square
                sf::Color(64, 224, 208, 120),  // Highlight
                sf::Color(230, 245, 250),      // Background
                sf::Color(255, 255, 255),      // Panel
                sf::Color(240, 248, 255),      // Panel light
                sf::Color(100, 149, 237),      // Border
                sf::Color(176, 196, 222),      // Divider
                sf::Color(0, 119, 190),        // Primary
                sf::Color(0, 99, 170),         // Primary hover
                sf::Color(230, 242, 255),      // Secondary
                sf::Color(210, 230, 250),      // Secondary hover
                sf::Color(220, 20, 60),        // Danger
                sf::Color(200, 0, 40),         // Danger hover
                sf::Color(64, 224, 208),       // Success
                sf::Color(44, 204, 188),       // Success hover
                sf::Color(0, 51, 102),         // Primary text
                sf::Color(70, 130, 180),       // Secondary text
                sf::Color(30, 144, 255),       // Accent text
                sf::Color(255, 255, 255)       // Text on dark
            );

        case ThemeType::LAVA:
            return Theme(
                sf::Color(50, 50, 50),         // Light square
                sf::Color(25, 25, 25),         // Dark square
                sf::Color(255, 69, 0, 150),    // Highlight
                sf::Color(30, 30, 30),         // Background
                sf::Color(40, 40, 40),         // Panel
                sf::Color(50, 50, 50),         // Panel light
                sf::Color(255, 69, 0),         // Border
                sf::Color(139, 69, 19),        // Divider
                sf::Color(255, 69, 0),         // Primary
                sf::Color(220, 50, 0),         // Primary hover
                sf::Color(60, 60, 60),         // Secondary
                sf::Color(80, 80, 80),         // Secondary hover
                sf::Color(178, 34, 34),        // Danger
                sf::Color(158, 20, 20),        // Danger hover
                sf::Color(255, 140, 0),        // Success
                sf::Color(235, 120, 0),        // Success hover
                sf::Color(255, 255, 224),      // Primary text
                sf::Color(255, 165, 0),        // Secondary text
                sf::Color(255, 99, 71),        // Accent text
                sf::Color(255, 255, 255)       // Text on dark
            );

        case ThemeType::ICE_PALACE:
            return Theme(
                sf::Color(240, 248, 255),      // Light square
                sf::Color(176, 224, 230),      // Dark square
                sf::Color(173, 216, 230, 120), // Highlight
                sf::Color(245, 255, 255),      // Background
                sf::Color(255, 255, 255),      // Panel
                sf::Color(248, 252, 255),      // Panel light
                sf::Color(135, 206, 235),      // Border
                sf::Color(176, 224, 230),      // Divider
                sf::Color(100, 149, 237),      // Primary
                sf::Color(70, 130, 220),       // Primary hover
                sf::Color(240, 248, 255),      // Secondary
                sf::Color(220, 235, 255),      // Secondary hover
                sf::Color(138, 43, 226),       // Danger
                sf::Color(118, 23, 206),       // Danger hover
                sf::Color(135, 206, 250),      // Success
                sf::Color(115, 186, 230),      // Success hover
                sf::Color(25, 25, 112),        // Primary text
                sf::Color(100, 149, 237),      // Secondary text
                sf::Color(65, 105, 225),       // Accent text
                sf::Color(255, 255, 255)       // Text on dark
            );

        case ThemeType::RETRO_ARCADE:
            return Theme(
                sf::Color(255, 255, 100),      // Light square
                sf::Color(255, 100, 255),      // Dark square
                sf::Color(0, 255, 255, 150),   // Highlight
                sf::Color(0, 0, 0),            // Background
                sf::Color(20, 20, 40),         // Panel
                sf::Color(30, 30, 50),         // Panel light
                sf::Color(255, 0, 255),        // Border
                sf::Color(0, 255, 255),        // Divider
                sf::Color(255, 0, 128),        // Primary
                sf::Color(220, 0, 108),        // Primary hover
                sf::Color(40, 40, 60),         // Secondary
                sf::Color(60, 60, 80),         // Secondary hover
                sf::Color(255, 50, 50),        // Danger
                sf::Color(235, 30, 30),        // Danger hover
                sf::Color(0, 255, 128),        // Success
                sf::Color(0, 235, 108),        // Success hover
                sf::Color(255, 255, 255),      // Primary text
                sf::Color(0, 255, 255),        // Secondary text
                sf::Color(255, 255, 0),        // Accent text
                sf::Color(255, 255, 255)       // Text on dark
            );

        case ThemeType::LAVENDER_DREAM:
            return Theme(
                sf::Color(243, 229, 245),      // Light square
                sf::Color(216, 191, 216),      // Dark square
                sf::Color(221, 160, 221, 120), // Highlight
                sf::Color(250, 245, 252),      // Background
                sf::Color(255, 255, 255),      // Panel
                sf::Color(248, 243, 250),      // Panel light
                sf::Color(216, 191, 216),      // Border
                sf::Color(230, 210, 235),      // Divider
                sf::Color(147, 112, 219),      // Primary
                sf::Color(127, 92, 199),       // Primary hover
                sf::Color(245, 235, 250),      // Secondary
                sf::Color(230, 215, 240),      // Secondary hover
                sf::Color(199, 21, 133),       // Danger
                sf::Color(179, 1, 113),        // Danger hover
                sf::Color(186, 85, 211),       // Success
                sf::Color(166, 65, 191),       // Success hover
                sf::Color(75, 0, 130),         // Primary text
                sf::Color(147, 112, 219),      // Secondary text
                sf::Color(138, 43, 226),       // Accent text
                sf::Color(255, 255, 255)       // Text on dark
            );

        case ThemeType::DESERT_SAND:
            return Theme(
                sf::Color(244, 228, 188),      // Light square
                sf::Color(210, 180, 140),      // Dark square
                sf::Color(255, 215, 0, 100),   // Highlight
                sf::Color(250, 240, 220),      // Background
                sf::Color(255, 255, 255),      // Panel
                sf::Color(252, 245, 230),      // Panel light
                sf::Color(205, 175, 135),      // Border
                sf::Color(222, 200, 170),      // Divider
                sf::Color(184, 134, 11),       // Primary
                sf::Color(164, 114, 0),        // Primary hover
                sf::Color(245, 235, 215),      // Secondary
                sf::Color(230, 220, 200),      // Secondary hover
                sf::Color(178, 34, 34),        // Danger
                sf::Color(158, 20, 20),        // Danger hover
                sf::Color(189, 183, 107),      // Success
                sf::Color(169, 163, 87),       // Success hover
                sf::Color(101, 67, 33),        // Primary text
                sf::Color(139, 90, 43),        // Secondary text
                sf::Color(184, 134, 11),       // Accent text
                sf::Color(255, 255, 255)       // Text on dark
            );

        case ThemeType::MINT_CHOCOLATE:
            return Theme(
                sf::Color(245, 255, 250),      // Light square
                sf::Color(152, 251, 152),      // Dark square
                sf::Color(189, 252, 201, 120), // Highlight
                sf::Color(248, 255, 252),      // Background
                sf::Color(255, 255, 255),      // Panel
                sf::Color(250, 255, 253),      // Panel light
                sf::Color(152, 251, 152),      // Border
                sf::Color(200, 252, 200),      // Divider
                sf::Color(72, 201, 176),       // Primary
                sf::Color(52, 181, 156),       // Primary hover
                sf::Color(245, 255, 250),      // Secondary
                sf::Color(230, 250, 240),      // Secondary hover
                sf::Color(199, 21, 133),       // Danger
                sf::Color(179, 1, 113),        // Danger hover
                sf::Color(144, 238, 144),      // Success
                sf::Color(124, 218, 124),      // Success hover
                sf::Color(47, 79, 79),         // Primary text
                sf::Color(60, 179, 113),       // Secondary text
                sf::Color(72, 201, 176),       // Accent text
                sf::Color(255, 255, 255)       // Text on dark
            );

        case ThemeType::VAMPIRE:
            return Theme(
                sf::Color(60, 20, 20),         // Light square
                sf::Color(30, 10, 10),         // Dark square
                sf::Color(139, 0, 0, 150),     // Highlight
                sf::Color(15, 5, 5),           // Background
                sf::Color(25, 10, 10),         // Panel
                sf::Color(40, 15, 15),         // Panel light
                sf::Color(139, 0, 0),          // Border
                sf::Color(70, 20, 20),         // Divider
                sf::Color(139, 0, 0),          // Primary
                sf::Color(119, 0, 0),          // Primary hover
                sf::Color(50, 20, 20),         // Secondary
                sf::Color(70, 30, 30),         // Secondary hover
                sf::Color(220, 20, 60),        // Danger
                sf::Color(200, 0, 40),         // Danger hover
                sf::Color(178, 34, 34),        // Success
                sf::Color(158, 20, 20),        // Success hover
                sf::Color(255, 215, 215),      // Primary text
                sf::Color(205, 92, 92),        // Secondary text
                sf::Color(220, 20, 60),        // Accent text
                sf::Color(255, 255, 255)       // Text on dark
            );

        case ThemeType::GOLD_RUSH:
            return Theme(
                sf::Color(255, 248, 220),      // Light square
                sf::Color(218, 165, 32),       // Dark square
                sf::Color(255, 215, 0, 120),   // Highlight
                sf::Color(255, 253, 240),      // Background
                sf::Color(255, 255, 255),      // Panel
                sf::Color(255, 250, 235),      // Panel light
                sf::Color(218, 165, 32),       // Border
                sf::Color(240, 200, 100),      // Divider
                sf::Color(184, 134, 11),       // Primary
                sf::Color(164, 114, 0),        // Primary hover
                sf::Color(255, 250, 205),      // Secondary
                sf::Color(250, 235, 180),      // Secondary hover
                sf::Color(178, 34, 34),        // Danger
                sf::Color(158, 20, 20),        // Danger hover
                sf::Color(255, 215, 0),        // Success
                sf::Color(235, 195, 0),        // Success hover
                sf::Color(101, 67, 33),        // Primary text
                sf::Color(184, 134, 11),       // Secondary text
                sf::Color(218, 165, 32),       // Accent text
                sf::Color(255, 255, 255)       // Text on dark
            );

        case ThemeType::AURORA:
            return Theme(
                sf::Color(230, 255, 250),      // Light square
                sf::Color(152, 255, 204),      // Dark square
                sf::Color(127, 255, 212, 120), // Highlight
                sf::Color(240, 255, 252),      // Background
                sf::Color(255, 255, 255),      // Panel
                sf::Color(245, 255, 253),      // Panel light
                sf::Color(127, 255, 212),      // Border
                sf::Color(175, 255, 230),      // Divider
                sf::Color(64, 224, 208),       // Primary
                sf::Color(44, 204, 188),       // Primary hover
                sf::Color(240, 255, 250),      // Secondary
                sf::Color(220, 250, 240),      // Secondary hover
                sf::Color(255, 20, 147),       // Danger
                sf::Color(235, 0, 127),        // Danger hover
                sf::Color(0, 255, 127),        // Success
                sf::Color(0, 235, 107),        // Success hover
                sf::Color(0, 100, 100),        // Primary text
                sf::Color(64, 224, 208),       // Secondary text
                sf::Color(72, 209, 204),       // Accent text
                sf::Color(255, 255, 255)       // Text on dark
            );

        case ThemeType::NOIR:
            return Theme(
                sf::Color(90, 90, 90),         // Light square
                sf::Color(40, 40, 40),         // Dark square
                sf::Color(200, 200, 200, 100), // Highlight
                sf::Color(20, 20, 20),         // Background
                sf::Color(30, 30, 30),         // Panel
                sf::Color(45, 45, 45),         // Panel light
                sf::Color(100, 100, 100),      // Border
                sf::Color(60, 60, 60),         // Divider
                sf::Color(150, 150, 150),      // Primary
                sf::Color(130, 130, 130),      // Primary hover
                sf::Color(50, 50, 50),         // Secondary
                sf::Color(70, 70, 70),         // Secondary hover
                sf::Color(180, 180, 180),      // Danger
                sf::Color(160, 160, 160),      // Danger hover
                sf::Color(200, 200, 200),      // Success
                sf::Color(180, 180, 180),      // Success hover
                sf::Color(220, 220, 220),      // Primary text
                sf::Color(150, 150, 150),      // Secondary text
                sf::Color(200, 200, 200),      // Accent text
                sf::Color(255, 255, 255)       // Text on dark
            );

        case ThemeType::BUBBLEGUM:
            return Theme(
                sf::Color(255, 240, 245),      // Light square
                sf::Color(255, 192, 203),      // Dark square
                sf::Color(255, 105, 180, 120), // Highlight
                sf::Color(255, 250, 252),      // Background
                sf::Color(255, 255, 255),      // Panel
                sf::Color(255, 245, 250),      // Panel light
                sf::Color(255, 182, 193),      // Border
                sf::Color(255, 218, 224),      // Divider
                sf::Color(255, 20, 147),       // Primary
                sf::Color(235, 0, 127),        // Primary hover
                sf::Color(255, 240, 245),      // Secondary
                sf::Color(255, 220, 230),      // Secondary hover
                sf::Color(220, 20, 60),        // Danger
                sf::Color(200, 0, 40),         // Danger hover
                sf::Color(255, 182, 193),      // Success
                sf::Color(235, 162, 173),      // Success hover
                sf::Color(199, 21, 133),       // Primary text
                sf::Color(255, 105, 180),      // Secondary text
                sf::Color(255, 20, 147),       // Accent text
                sf::Color(255, 255, 255)       // Text on dark
            );

        case ThemeType::TOXIC:
            return Theme(
                sf::Color(173, 255, 47),       // Light square
                sf::Color(50, 205, 50),        // Dark square
                sf::Color(0, 255, 0, 150),     // Highlight
                sf::Color(20, 30, 20),         // Background
                sf::Color(30, 40, 30),         // Panel
                sf::Color(40, 50, 40),         // Panel light
                sf::Color(0, 255, 0),          // Border
                sf::Color(50, 205, 50),        // Divider
                sf::Color(0, 250, 0),          // Primary
                sf::Color(0, 220, 0),          // Primary hover
                sf::Color(40, 50, 40),         // Secondary
                sf::Color(60, 70, 60),         // Secondary hover
                sf::Color(255, 50, 50),        // Danger
                sf::Color(235, 30, 30),        // Danger hover
                sf::Color(50, 205, 50),        // Success
                sf::Color(30, 185, 30),        // Success hover
                sf::Color(173, 255, 47),       // Primary text
                sf::Color(124, 252, 0),        // Secondary text
                sf::Color(0, 255, 0),          // Accent text
                sf::Color(255, 255, 255)       // Text on dark
            );

        case ThemeType::ROYAL_PURPLE:
            return Theme(
                sf::Color(230, 220, 240),      // Light square
                sf::Color(147, 112, 219),      // Dark square
                sf::Color(138, 43, 226, 120),  // Highlight
                sf::Color(245, 240, 250),      // Background
                sf::Color(255, 255, 255),      // Panel
                sf::Color(250, 245, 255),      // Panel light
                sf::Color(147, 112, 219),      // Border
                sf::Color(186, 170, 230),      // Divider
                sf::Color(75, 0, 130),         // Primary
                sf::Color(55, 0, 110),         // Primary hover
                sf::Color(240, 230, 250),      // Secondary
                sf::Color(225, 210, 240),      // Secondary hover
                sf::Color(199, 21, 133),       // Danger
                sf::Color(179, 1, 113),        // Danger hover
                sf::Color(138, 43, 226),       // Success
                sf::Color(118, 23, 206),       // Success hover
                sf::Color(48, 25, 52),         // Primary text
                sf::Color(102, 51, 153),       // Secondary text
                sf::Color(138, 43, 226),       // Accent text
                sf::Color(255, 255, 255)       // Text on dark
            );

        case ThemeType::MATRIX:
            return Theme(
                sf::Color(0, 40, 0),           // Light square
                sf::Color(0, 20, 0),           // Dark square
                sf::Color(0, 255, 0, 150),     // Highlight
                sf::Color(0, 0, 0),            // Background
                sf::Color(0, 15, 0),           // Panel
                sf::Color(0, 25, 0),           // Panel light
                sf::Color(0, 255, 0),          // Border
                sf::Color(0, 100, 0),          // Divider
                sf::Color(0, 255, 0),          // Primary
                sf::Color(0, 220, 0),          // Primary hover
                sf::Color(0, 30, 0),           // Secondary
                sf::Color(0, 50, 0),           // Secondary hover
                sf::Color(255, 0, 0),          // Danger
                sf::Color(220, 0, 0),          // Danger hover
                sf::Color(0, 200, 0),          // Success
                sf::Color(0, 170, 0),          // Success hover
                sf::Color(0, 255, 0),          // Primary text
                sf::Color(0, 200, 0),          // Secondary text
                sf::Color(0, 255, 100),        // Accent text
                sf::Color(0, 255, 0)           // Text on dark
            );

        default:
            return getTheme(ThemeType::CLASSIC);
    }
}
