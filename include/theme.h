#pragma once
#include <SFML/Graphics.hpp>

struct Theme {
private:
    //board colors
    sf::Color LIGHT_COLOR;
    sf::Color DARK_COLOR;
    sf::Color HIGHLIGHT_COLOR;

    //ui colors
    sf::Color UI_BACKGROUND;
    sf::Color UI_PANEL;
    sf::Color UI_PANEL_LIGHT;
    sf::Color UI_BORDER;
    sf::Color UI_DIVIDER;

    //button colors
    sf::Color BUTTON_PRIMARY;
    sf::Color BUTTON_PRIMARY_HOVER;
    sf::Color BUTTON_SECONDARY;
    sf::Color BUTTON_SECONDARY_HOVER;
    sf::Color BUTTON_DANGER;
    sf::Color BUTTON_DANGER_HOVER;
    sf::Color BUTTON_SUCCESS;
    sf::Color BUTTON_SUCCESS_HOVER;

    //text colors
    sf::Color TEXT_PRIMARY;
    sf::Color TEXT_SECONDARY;
    sf::Color TEXT_ACCENT;
    sf::Color TEXT_ON_DARK;

public:
    Theme(
        sf::Color light, sf::Color dark, sf::Color highlight,
        sf::Color uiBg, sf::Color uiPanel, sf::Color uiPanelLight, sf::Color uiBorder, sf::Color uiDivider,
        sf::Color btnPrimary, sf::Color btnPrimaryHover,
        sf::Color btnSecondary, sf::Color btnSecondaryHover,
        sf::Color btnDanger, sf::Color btnDangerHover,
        sf::Color btnSuccess, sf::Color btnSuccessHover,
        sf::Color textPrimary, sf::Color textSecondary, sf::Color textAccent, sf::Color textOnDark
    ) : LIGHT_COLOR(light), DARK_COLOR(dark), HIGHLIGHT_COLOR(highlight),
        UI_BACKGROUND(uiBg), UI_PANEL(uiPanel), UI_PANEL_LIGHT(uiPanelLight), UI_BORDER(uiBorder), UI_DIVIDER(uiDivider),
        BUTTON_PRIMARY(btnPrimary), BUTTON_PRIMARY_HOVER(btnPrimaryHover),
        BUTTON_SECONDARY(btnSecondary), BUTTON_SECONDARY_HOVER(btnSecondaryHover),
        BUTTON_DANGER(btnDanger), BUTTON_DANGER_HOVER(btnDangerHover),
        BUTTON_SUCCESS(btnSuccess), BUTTON_SUCCESS_HOVER(btnSuccessHover),
        TEXT_PRIMARY(textPrimary), TEXT_SECONDARY(textSecondary), TEXT_ACCENT(textAccent), TEXT_ON_DARK(textOnDark) {}

    sf::Color getLc() const { return LIGHT_COLOR; }
    sf::Color getDc() const { return DARK_COLOR; }
    sf::Color getHc() const { return HIGHLIGHT_COLOR; }

    sf::Color getUiBg() const { return UI_BACKGROUND; }
    sf::Color getUiPanel() const { return UI_PANEL; }
    sf::Color getUiPanelLight() const { return UI_PANEL_LIGHT; }
    sf::Color getUiBorder() const { return UI_BORDER; }
    sf::Color getUiDivider() const { return UI_DIVIDER; }

    sf::Color getBtnPrimary() const { return BUTTON_PRIMARY; }
    sf::Color getBtnPrimaryHover() const { return BUTTON_PRIMARY_HOVER; }
    sf::Color getBtnSecondary() const { return BUTTON_SECONDARY; }
    sf::Color getBtnSecondaryHover() const { return BUTTON_SECONDARY_HOVER; }
    sf::Color getBtnDanger() const { return BUTTON_DANGER; }
    sf::Color getBtnDangerHover() const { return BUTTON_DANGER_HOVER; }
    sf::Color getBtnSuccess() const { return BUTTON_SUCCESS; }
    sf::Color getBtnSuccessHover() const { return BUTTON_SUCCESS_HOVER; }

    sf::Color getTextPrimary() const { return TEXT_PRIMARY; }
    sf::Color getTextSecondary() const { return TEXT_SECONDARY; }
    sf::Color getTextAccent() const { return TEXT_ACCENT; }
    sf::Color getTextOnDark() const { return TEXT_ON_DARK; }
};

enum class ThemeType {
    CLASSIC,
    MODERN,
    BLUE,
    DARK,
    NEON_CYBERPUNK,
    SAKURA,
    FOREST,
    SUNSET,
    OCEAN_DEEP,
    LAVA,
    ICE_PALACE,
    RETRO_ARCADE,
    LAVENDER_DREAM,
    DESERT_SAND,
    MINT_CHOCOLATE,
    VAMPIRE,
    GOLD_RUSH,
    AURORA,
    NOIR,
    BUBBLEGUM,
    TOXIC,
    ROYAL_PURPLE,
    MATRIX
};

Theme getTheme(ThemeType type);
