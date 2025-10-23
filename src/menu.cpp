#include "menu.h"

Menu::Menu(tgui::Gui& gui, Theme& theme) : gui(gui), theme(theme), choice(MENU_CHOICE::NONE), showing(false), selectedThemeType(ThemeType::LIGHT), themeChanged(false) {
    createMainMenuView();
}

void Menu::createMainMenuView() {
    sf::Color bgColor = theme.getUiBg();
    sf::Color panelColor = theme.getUiPanel();
    sf::Color textPrimary = theme.getTextPrimary();
    sf::Color textSecondary = theme.getTextSecondary();

    // Full-screen container with themed background
    auto panel = tgui::Panel::create();
    panel->setSize("100%", "100%");
    panel->setPosition(0, 0);
    panel->getRenderer()->setBackgroundColor(tgui::Color(bgColor.r, bgColor.g, bgColor.b, bgColor.a));
    panel->setVisible(false);
    gui.add(panel, "MainMenu");

    // Main content container - no visible background, just content
    auto contentPanel = tgui::Panel::create();
    contentPanel->setSize(550, 650);
    contentPanel->setPosition("50%", "50%");
    contentPanel->setOrigin(0.5f, 0.5f);
    contentPanel->getRenderer()->setBackgroundColor(tgui::Color(0, 0, 0, 0));
    contentPanel->getRenderer()->setBorders(0);
    panel->add(contentPanel);

    // Title - light, clean, prominent
    auto titleLabel = tgui::Label::create();
    titleLabel->setText("C H E S S");
    titleLabel->setPosition(275, 80);
    titleLabel->setOrigin(0.5f, 0.5f);
    titleLabel->setTextSize(56);
    titleLabel->getRenderer()->setTextColor(tgui::Color(textPrimary.r, textPrimary.g, textPrimary.b, 255));
    contentPanel->add(titleLabel);

    // Subtitle - visible with proper contrast
    auto subtitleLabel = tgui::Label::create();
    subtitleLabel->setText("0.0.1");
    subtitleLabel->setPosition(275, 145);
    subtitleLabel->setOrigin(0.5f, 0.5f);
    subtitleLabel->setTextSize(16);
    subtitleLabel->getRenderer()->setTextColor(tgui::Color(textSecondary.r, textSecondary.g, textSecondary.b, 255));
    contentPanel->add(subtitleLabel);

    // Calculate button colors based on theme
    sf::Color primaryBtnBg, primaryBtnHover, secondaryBtnBg, secondaryBtnHover;
    if(panelColor.r > 200) { // Light theme
        primaryBtnBg = sf::Color(220, 220, 230, 255);
        primaryBtnHover = sf::Color(200, 200, 215, 255);
        secondaryBtnBg = sf::Color(235, 235, 242, 255);
        secondaryBtnHover = sf::Color(215, 215, 225, 255);
    } else { // Dark theme
        primaryBtnBg = sf::Color(55, 55, 62, 255);
        primaryBtnHover = sf::Color(75, 75, 85, 255);
        secondaryBtnBg = sf::Color(45, 45, 52, 255);
        secondaryBtnHover = sf::Color(65, 65, 75, 255);
    }

    // Primary button - prominent, rounded
    auto spBtn = tgui::Button::create();
    spBtn->setText("Single Player");
    spBtn->setSize(420, 56);
    spBtn->setPosition(275, 240);
    spBtn->setOrigin(0.5f, 0.5f);
    spBtn->setTextSize(15);
    spBtn->getRenderer()->setBackgroundColor(tgui::Color(primaryBtnBg.r, primaryBtnBg.g, primaryBtnBg.b, primaryBtnBg.a));
    spBtn->getRenderer()->setBackgroundColorHover(tgui::Color(primaryBtnHover.r, primaryBtnHover.g, primaryBtnHover.b, primaryBtnHover.a));
    spBtn->getRenderer()->setTextColor(tgui::Color(textPrimary.r, textPrimary.g, textPrimary.b, 255));
    spBtn->getRenderer()->setBorders(0);
    spBtn->getRenderer()->setRoundedBorderRadius(12);
    spBtn->onPress([this] { choice = MENU_CHOICE::SINGLE_PLAYER; });
    contentPanel->add(spBtn);

    // Secondary buttons - same style, generous spacing
    auto createButton = [&](const std::string& text, float y) {
        auto btn = tgui::Button::create();
        btn->setText(text);
        btn->setSize(420, 56);
        btn->setPosition(275, y);
        btn->setOrigin(0.5f, 0.5f);
        btn->setTextSize(15);
        btn->getRenderer()->setBackgroundColor(tgui::Color(secondaryBtnBg.r, secondaryBtnBg.g, secondaryBtnBg.b, secondaryBtnBg.a));
        btn->getRenderer()->setBackgroundColorHover(tgui::Color(secondaryBtnHover.r, secondaryBtnHover.g, secondaryBtnHover.b, secondaryBtnHover.a));
        btn->getRenderer()->setTextColor(tgui::Color(textPrimary.r, textPrimary.g, textPrimary.b, 255));
        btn->getRenderer()->setBorders(0);
        btn->getRenderer()->setRoundedBorderRadius(12);
        return btn;
    };

    auto mpBtn = createButton("Multiplayer", 326);
    mpBtn->onPress([this] { choice = MENU_CHOICE::MULTIPLAYER; });
    contentPanel->add(mpBtn);

    auto settingsBtn = createButton("Settings", 412);
    settingsBtn->onPress([this] { showSettingsDialog(); });
    contentPanel->add(settingsBtn);

    // Quit button - minimal text link style
    auto quitBtn = tgui::Button::create();
    quitBtn->setText("Quit");
    quitBtn->setSize(100, 40);
    quitBtn->setPosition(275, 530);
    quitBtn->setOrigin(0.5f, 0.5f);
    quitBtn->setTextSize(13);
    quitBtn->getRenderer()->setBackgroundColor(tgui::Color(0, 0, 0, 0));
    quitBtn->getRenderer()->setBackgroundColorHover(tgui::Color(255, 255, 255, 15));
    quitBtn->getRenderer()->setTextColor(tgui::Color(textSecondary.r, textSecondary.g, textSecondary.b, 180));
    quitBtn->getRenderer()->setBorders(0);
    quitBtn->getRenderer()->setRoundedBorderRadius(8);
    quitBtn->onPress([this] { choice = MENU_CHOICE::QUIT; });
    contentPanel->add(quitBtn);
}

void Menu::show() {
    auto panel = gui.get<tgui::Panel>("MainMenu");
    if(panel) {
        panel->setVisible(true);
        showing = true;
    }
}

void Menu::hide() {
    auto panel = gui.get<tgui::Panel>("MainMenu");
    if(panel) {
        panel->setVisible(false);
        showing = false;
    }
}

void Menu::showSettingsDialog() {
    sf::Color panelBg = theme.getUiPanel();
    sf::Color textPrimary = theme.getTextPrimary();

    // Theme-aware colors
    sf::Color dialogBg, btnBg, btnHover;
    if(panelBg.r > 200) { // Light theme
        dialogBg = sf::Color(245, 245, 250, 255);
        btnBg = sf::Color(235, 235, 242, 255);
        btnHover = sf::Color(215, 215, 225, 255);
    } else { // Dark theme
        dialogBg = sf::Color(28, 28, 32, 255);
        btnBg = sf::Color(45, 45, 52, 255);
        btnHover = sf::Color(65, 65, 75, 255);
    }

    auto overlay = tgui::Panel::create();
    overlay->setSize("100%", "100%");
    overlay->getRenderer()->setBackgroundColor(tgui::Color(0, 0, 0, 200));
    gui.add(overlay, "SettingsOverlay");

    auto dialog = tgui::Panel::create();
    dialog->setSize(480, 320);
    dialog->setPosition("50%", "50%");
    dialog->setOrigin(0.5f, 0.5f);
    dialog->getRenderer()->setBackgroundColor(tgui::Color(dialogBg.r, dialogBg.g, dialogBg.b, dialogBg.a));
    dialog->getRenderer()->setBorders(0);
    dialog->getRenderer()->setRoundedBorderRadius(16);
    overlay->add(dialog);

    auto titleLabel = tgui::Label::create();
    titleLabel->setText("Settings");
    titleLabel->setPosition(240, 45);
    titleLabel->setOrigin(0.5f, 0.5f);
    titleLabel->setTextSize(24);
    titleLabel->getRenderer()->setTextColor(tgui::Color(textPrimary.r, textPrimary.g, textPrimary.b, 255));
    dialog->add(titleLabel);

    auto themeLabel = tgui::Label::create();
    themeLabel->setText("Appearance");
    themeLabel->setPosition(40, 100);
    themeLabel->setTextSize(14);
    themeLabel->getRenderer()->setTextColor(tgui::Color(textPrimary.r, textPrimary.g, textPrimary.b, 200));
    dialog->add(themeLabel);

    auto lightBtn = tgui::Button::create();
    lightBtn->setText("Light");
    lightBtn->setSize(190, 48);
    lightBtn->setPosition(40, 135);
    lightBtn->setTextSize(14);
    lightBtn->getRenderer()->setBackgroundColor(tgui::Color(btnBg.r, btnBg.g, btnBg.b, btnBg.a));
    lightBtn->getRenderer()->setBackgroundColorHover(tgui::Color(btnHover.r, btnHover.g, btnHover.b, btnHover.a));
    lightBtn->getRenderer()->setTextColor(tgui::Color(textPrimary.r, textPrimary.g, textPrimary.b, 255));
    lightBtn->getRenderer()->setBorders(0);
    lightBtn->getRenderer()->setRoundedBorderRadius(10);
    lightBtn->onPress([this] {
        selectedThemeType = ThemeType::LIGHT;
        themeChanged = true;
    });
    dialog->add(lightBtn);

    auto darkBtn = tgui::Button::create();
    darkBtn->setText("Dark");
    darkBtn->setSize(190, 48);
    darkBtn->setPosition(250, 135);
    darkBtn->setTextSize(14);
    darkBtn->getRenderer()->setBackgroundColor(tgui::Color(btnBg.r, btnBg.g, btnBg.b, btnBg.a));
    darkBtn->getRenderer()->setBackgroundColorHover(tgui::Color(btnHover.r, btnHover.g, btnHover.b, btnHover.a));
    darkBtn->getRenderer()->setTextColor(tgui::Color(textPrimary.r, textPrimary.g, textPrimary.b, 255));
    darkBtn->getRenderer()->setBorders(0);
    darkBtn->getRenderer()->setRoundedBorderRadius(10);
    darkBtn->onPress([this] {
        selectedThemeType = ThemeType::DARK;
        themeChanged = true;
    });
    dialog->add(darkBtn);

    sf::Color closeBtnBg = (panelBg.r > 200) ? sf::Color(220, 220, 230, 255) : sf::Color(55, 55, 62, 255);
    sf::Color closeBtnHover = (panelBg.r > 200) ? sf::Color(200, 200, 215, 255) : sf::Color(75, 75, 85, 255);

    auto closeBtn = tgui::Button::create();
    closeBtn->setText("Close");
    closeBtn->setSize(400, 48);
    closeBtn->setPosition(240, 240);
    closeBtn->setOrigin(0.5f, 0.5f);
    closeBtn->setTextSize(14);
    closeBtn->getRenderer()->setBackgroundColor(tgui::Color(closeBtnBg.r, closeBtnBg.g, closeBtnBg.b, closeBtnBg.a));
    closeBtn->getRenderer()->setBackgroundColorHover(tgui::Color(closeBtnHover.r, closeBtnHover.g, closeBtnHover.b, closeBtnHover.a));
    closeBtn->getRenderer()->setTextColor(tgui::Color(textPrimary.r, textPrimary.g, textPrimary.b, 255));
    closeBtn->getRenderer()->setBorders(0);
    closeBtn->getRenderer()->setRoundedBorderRadius(10);
    closeBtn->onPress([this, overlay] {
        gui.remove(overlay);
    });
    dialog->add(closeBtn);
}

GameUI::GameUI(tgui::Gui& gui, Theme& theme) : gui(gui), theme(theme) {
}

void GameUI::show() {
    sf::Color panelBg = theme.getUiPanel();
    sf::Color textPrimary = theme.getTextPrimary();
    sf::Color textSecondary = theme.getTextSecondary();

    // Theme-aware panel color
    sf::Color sidePanelBg = (panelBg.r > 200) ? sf::Color(240, 240, 245, 250) : sf::Color(18, 18, 22, 250);

    auto leftPanel = tgui::Panel::create();
    leftPanel->setSize(340, "100%");
    leftPanel->setPosition(0, 0);
    leftPanel->getRenderer()->setBackgroundColor(tgui::Color(sidePanelBg.r, sidePanelBg.g, sidePanelBg.b, sidePanelBg.a));
    leftPanel->getRenderer()->setBorders(0);
    gui.add(leftPanel, "GameUIPanel");

    auto titleLabel = tgui::Label::create();
    titleLabel->setText("C H E S S");
    titleLabel->setPosition(170, 35);
    titleLabel->setOrigin(0.5f, 0.5f);
    titleLabel->setTextSize(24);
    titleLabel->getRenderer()->setTextColor(tgui::Color(textPrimary.r, textPrimary.g, textPrimary.b, 255));
    leftPanel->add(titleLabel);

    turnLabel = tgui::Label::create();
    turnLabel->setText("Turn: White");
    turnLabel->setPosition(30, 90);
    turnLabel->setTextSize(16);
    turnLabel->getRenderer()->setTextColor(tgui::Color(textPrimary.r, textPrimary.g, textPrimary.b, 255));
    leftPanel->add(turnLabel);

    statusLabel = tgui::Label::create();
    statusLabel->setText("");
    statusLabel->setPosition(30, 120);
    statusLabel->setTextSize(15);
    statusLabel->getRenderer()->setTextColor(tgui::Color(textSecondary.r, textSecondary.g, textSecondary.b, 255));
    leftPanel->add(statusLabel);

    sf::Color menuBtnBg = (panelBg.r > 200) ? sf::Color(220, 220, 230, 255) : sf::Color(45, 45, 52, 255);
    sf::Color menuBtnHover = (panelBg.r > 200) ? sf::Color(200, 200, 215, 255) : sf::Color(65, 65, 75, 255);

    menuButton = tgui::Button::create();
    menuButton->setText("Menu");
    menuButton->setSize(280, 48);
    menuButton->setPosition(30, 720);
    menuButton->setTextSize(14);
    menuButton->getRenderer()->setBackgroundColor(tgui::Color(menuBtnBg.r, menuBtnBg.g, menuBtnBg.b, menuBtnBg.a));
    menuButton->getRenderer()->setBackgroundColorHover(tgui::Color(menuBtnHover.r, menuBtnHover.g, menuBtnHover.b, menuBtnHover.a));
    menuButton->getRenderer()->setTextColor(tgui::Color(textPrimary.r, textPrimary.g, textPrimary.b, 255));
    menuButton->getRenderer()->setBorders(0);
    menuButton->getRenderer()->setRoundedBorderRadius(10);
    menuButton->onPress([this] {
        if(onMenuPressed) onMenuPressed();
    });
    leftPanel->add(menuButton);
}

void GameUI::hide() {
    auto panel = gui.get("GameUIPanel");
    if(panel) gui.remove(panel);
}

void GameUI::updateTurn(const std::string& color) {
    if(turnLabel) turnLabel->setText("Turn: " + color);
}

void GameUI::updateStatus(const std::string& status) {
    if(statusLabel) statusLabel->setText(status);
}

void GameUI::setMenuCallback(std::function<void()> callback) {
    onMenuPressed = callback;
}

void GameUI::showGameOverDialog(const std::string& message, std::function<void()> onRestart, std::function<void()> onQuit) {
    sf::Color textPrimary = theme.getTextPrimary();

    auto overlay = tgui::Panel::create();
    overlay->setSize("100%", "100%");
    overlay->getRenderer()->setBackgroundColor(tgui::Color(0, 0, 0, 200));
    gui.add(overlay, "GameOverOverlay");

    auto dialog = tgui::Panel::create();
    dialog->setSize(480, 260);
    dialog->setPosition("50%", "50%");
    dialog->setOrigin(0.5f, 0.5f);
    dialog->getRenderer()->setBackgroundColor(tgui::Color(28, 28, 32, 255));
    dialog->getRenderer()->setBorders(0);
    dialog->getRenderer()->setRoundedBorderRadius(16);
    overlay->add(dialog);

    auto messageLabel = tgui::Label::create();
    messageLabel->setText(message);
    messageLabel->setPosition(240, 75);
    messageLabel->setOrigin(0.5f, 0.5f);
    messageLabel->setTextSize(22);
    messageLabel->getRenderer()->setTextColor(tgui::Color(textPrimary.r, textPrimary.g, textPrimary.b, 255));
    dialog->add(messageLabel);

    auto restartBtn = tgui::Button::create();
    restartBtn->setText("Restart");
    restartBtn->setSize(200, 50);
    restartBtn->setPosition(40, 165);
    restartBtn->setTextSize(14);
    restartBtn->getRenderer()->setBackgroundColor(tgui::Color(55, 55, 62, 255));
    restartBtn->getRenderer()->setBackgroundColorHover(tgui::Color(75, 75, 85, 255));
    restartBtn->getRenderer()->setTextColor(tgui::Color(textPrimary.r, textPrimary.g, textPrimary.b, 255));
    restartBtn->getRenderer()->setBorders(0);
    restartBtn->getRenderer()->setRoundedBorderRadius(10);
    restartBtn->onPress([this, overlay, onRestart] {
        gui.remove(overlay);
        if(onRestart) onRestart();
    });
    dialog->add(restartBtn);

    auto quitBtn = tgui::Button::create();
    quitBtn->setText("Menu");
    quitBtn->setSize(200, 50);
    quitBtn->setPosition(260, 165);
    quitBtn->setTextSize(14);
    quitBtn->getRenderer()->setBackgroundColor(tgui::Color(45, 45, 52, 255));
    quitBtn->getRenderer()->setBackgroundColorHover(tgui::Color(65, 65, 75, 255));
    quitBtn->getRenderer()->setTextColor(tgui::Color(textPrimary.r, textPrimary.g, textPrimary.b, 255));
    quitBtn->getRenderer()->setBorders(0);
    quitBtn->getRenderer()->setRoundedBorderRadius(10);
    quitBtn->onPress([this, overlay, onQuit] {
        gui.remove(overlay);
        if(onQuit) onQuit();
    });
    dialog->add(quitBtn);
}

void GameUI::showPromotionDialog(PIECE_COLOR color, std::function<void(PIECE_TYPE)> onSelect) {
    sf::Color textPrimary = theme.getTextPrimary();

    auto overlay = tgui::Panel::create();
    overlay->setSize("100%", "100%");
    overlay->getRenderer()->setBackgroundColor(tgui::Color(0, 0, 0, 200));
    gui.add(overlay, "PromotionOverlay");

    auto dialog = tgui::Panel::create();
    dialog->setSize(580, 230);
    dialog->setPosition("50%", "50%");
    dialog->setOrigin(0.5f, 0.5f);
    dialog->getRenderer()->setBackgroundColor(tgui::Color(28, 28, 32, 255));
    dialog->getRenderer()->setBorders(0);
    dialog->getRenderer()->setRoundedBorderRadius(16);
    overlay->add(dialog);

    auto titleLabel = tgui::Label::create();
    titleLabel->setText("Promote Pawn");
    titleLabel->setPosition(290, 45);
    titleLabel->setOrigin(0.5f, 0.5f);
    titleLabel->setTextSize(20);
    titleLabel->getRenderer()->setTextColor(tgui::Color(textPrimary.r, textPrimary.g, textPrimary.b, 255));
    dialog->add(titleLabel);

    std::vector<std::pair<PIECE_TYPE, std::string>> pieces = {
        {PIECE_TYPE::QUEEN, "Queen"},
        {PIECE_TYPE::ROOK, "Rook"},
        {PIECE_TYPE::BISHOP, "Bishop"},
        {PIECE_TYPE::KNIGHT, "Knight"}
    };

    for(size_t i = 0; i < pieces.size(); i++) {
        auto btn = tgui::Button::create();
        btn->setText(pieces[i].second);
        btn->setSize(120, 68);
        btn->setPosition(50 + i * 130, 115);
        btn->setTextSize(14);
        btn->getRenderer()->setBackgroundColor(tgui::Color(45, 45, 52, 255));
        btn->getRenderer()->setBackgroundColorHover(tgui::Color(65, 65, 75, 255));
        btn->getRenderer()->setTextColor(tgui::Color(textPrimary.r, textPrimary.g, textPrimary.b, 255));
        btn->getRenderer()->setBorders(0);
        btn->getRenderer()->setRoundedBorderRadius(10);

        auto pieceType = pieces[i].first;
        btn->onPress([this, overlay, onSelect, pieceType] {
            gui.remove(overlay);
            if(onSelect) onSelect(pieceType);
        });
        dialog->add(btn);
    }
}
