#include "menu.h"

Menu::Menu(tgui::Gui& gui, Theme& theme) : gui(gui), theme(theme), choice(MENU_CHOICE::NONE), showing(false), selectedThemeType(ThemeType::DARK), themeChanged(false) {
}

void Menu::show() {
    showing = true;
    createMainMenuView();
}

void Menu::hide() {
    showing = false;
    gui.removeAllWidgets();
}


//creates the general main view. all widgets made here
void Menu::createMainMenuView() {
    gui.removeAllWidgets();
    
    
    //bg
    auto bgPanel = tgui::Panel::create();
    bgPanel->setSize("100%", "100%");
    sf::Color uiBg = theme.getUiBg(); 
    bgPanel->getRenderer()->setBackgroundColor(tgui::Color(uiBg.r, uiBg.g, uiBg.b));
    gui.add(bgPanel);

    //main container div
    auto panel = tgui::Panel::create();
    panel->setSize(520, 550);
    panel->setPosition("50%", "50%");
    panel->setOrigin(sf::Vector2f(0.5f, 0.5f));

    sf::Color panelColor = theme.getUiPanel();
    sf::Color borderColor = theme.getUiBorder();
    panel->getRenderer()->setBackgroundColor(tgui::Color(panelColor.r, panelColor.g, panelColor.b));
    panel->getRenderer()->setBorderColor(tgui::Color(borderColor.r, borderColor.g, borderColor.b));
    panel->getRenderer()->setBorders(1);
    panel->getRenderer()->setRoundedBorderRadius(12);
    gui.add(panel);
    
    
    //title
    auto title = tgui::Label::create();
    title->setText("CHESS");
    title->setTextSize(48);
    sf::Color textPrimary = theme.getTextPrimary();
    title->getRenderer()->setTextColor(tgui::Color(textPrimary.r, textPrimary.g, textPrimary.b));
    title->setPosition("50%", 50);
    title->setOrigin(0.5f, 0.0f);
    panel->add(title);


    //subheading
    auto subtitle = tgui::Label::create();
    subtitle->setText("Select Game Mode");
    subtitle->setTextSize(16);
    sf::Color textSecondary = theme.getTextSecondary();
    subtitle->getRenderer()->setTextColor(tgui::Color(textSecondary.r, textSecondary.g, textSecondary.b));
    subtitle->setPosition("50%", 115);
    subtitle->setOrigin(0.5f, 0.0f);
    panel->add(subtitle);
    
    //button styler
    auto styleButton = [](tgui::Button::Ptr btn, tgui::Color mainColor, tgui::Color hoverColor, tgui::Color textColor) {
        btn->getRenderer()->setBackgroundColor(mainColor);
        btn->getRenderer()->setBackgroundColorHover(hoverColor);
        btn->getRenderer()->setBackgroundColorDown(mainColor);
        btn->getRenderer()->setTextColor(textColor);
        btn->getRenderer()->setTextColorHover(textColor);
        btn->getRenderer()->setBorderColor(tgui::Color(0, 0, 0, 0));
        btn->getRenderer()->setBorders(0);
        btn->getRenderer()->setRoundedBorderRadius(8);
        btn->setTextSize(16);
    };
    
    //BUTTONS
    
    
    //get theme colors
    sf::Color btnPrimary = theme.getBtnPrimary();
    sf::Color btnPrimaryHover = theme.getBtnPrimaryHover();
    sf::Color btnSuccess = theme.getBtnSuccess();
    sf::Color btnSuccessHover = theme.getBtnSuccessHover();
    sf::Color btnSecondary = theme.getBtnSecondary();
    sf::Color btnSecondaryHover = theme.getBtnSecondaryHover();
    sf::Color btnDanger = theme.getBtnDanger();
    sf::Color btnDangerHover = theme.getBtnDangerHover();
    sf::Color textOnDark = theme.getTextOnDark();

    //single player
    auto spBtn = tgui::Button::create();
    spBtn->setText("Single Player");
    spBtn->setSize(420, 65);
    spBtn->setPosition("50%", 165);
    spBtn->setOrigin(0.5f, 0.0f);
    styleButton(spBtn,
        tgui::Color(btnPrimary.r, btnPrimary.g, btnPrimary.b),
        tgui::Color(btnPrimaryHover.r, btnPrimaryHover.g, btnPrimaryHover.b),
        tgui::Color(textOnDark.r, textOnDark.g, textOnDark.b));
    spBtn->onPress([this] {
        choice = MENU_CHOICE::SINGLE_PLAYER;
        hide();
    });
    panel->add(spBtn);

    //multiplayer
    auto mpBtn = tgui::Button::create();
    mpBtn->setText("Online Multiplayer");
    mpBtn->setSize(420, 65);
    mpBtn->setPosition("50%", 250);
    mpBtn->setOrigin(0.5f, 0.0f);
    styleButton(mpBtn,
        tgui::Color(btnSuccess.r, btnSuccess.g, btnSuccess.b),
        tgui::Color(btnSuccessHover.r, btnSuccessHover.g, btnSuccessHover.b),
        tgui::Color(textOnDark.r, textOnDark.g, textOnDark.b));
    mpBtn->onPress([this] {
        choice = MENU_CHOICE::MULTIPLAYER;
        hide();
    });
    panel->add(mpBtn);


    //settings
    auto settingsBtn = tgui::Button::create();
    settingsBtn->setText("Settings");
    settingsBtn->setSize(420, 55);
    settingsBtn->setPosition("50%", 345);
    settingsBtn->setOrigin(0.5f, 0.0f);
    styleButton(settingsBtn,
        tgui::Color(btnSecondary.r, btnSecondary.g, btnSecondary.b),
        tgui::Color(btnSecondaryHover.r, btnSecondaryHover.g, btnSecondaryHover.b),
        tgui::Color(textPrimary.r, textPrimary.g, textPrimary.b));
    settingsBtn->onPress([this] {
        showSettingsDialog();
    });
    panel->add(settingsBtn);

    //quit
    auto quitBtn = tgui::Button::create();
    quitBtn->setText("Quit");
    quitBtn->setSize(420, 55);
    quitBtn->setPosition("50%", 420);
    quitBtn->setOrigin(0.5f, 0.0f);
    styleButton(quitBtn,
        tgui::Color(btnDanger.r, btnDanger.g, btnDanger.b),
        tgui::Color(btnDangerHover.r, btnDangerHover.g, btnDangerHover.b),
        tgui::Color(textOnDark.r, textOnDark.g, textOnDark.b));
    quitBtn->onPress([this] {
        choice = MENU_CHOICE::QUIT;
        hide();
    });
    panel->add(quitBtn);
}

void Menu::showMessage(const std::string &title, const std::string &message) {
    auto messageBox = tgui::MessageBox::create();
    messageBox->setTitle(title);
    messageBox->setText(message);
    messageBox->addButton("OK");
    messageBox->setPosition("50%", "50%");
    messageBox->setOrigin(sf::Vector2f(0.5f, 0.5f));
    gui.add(messageBox);
}

void Menu::showSettingsDialog() {
    //get theme colors
    sf::Color panelBg = theme.getUiPanel();
    sf::Color borderColor = theme.getUiBorder();
    sf::Color dividerColor = theme.getUiDivider();
    sf::Color textPrimary = theme.getTextPrimary();
    sf::Color textSecondary = theme.getTextSecondary();
    sf::Color textOnDark = theme.getTextOnDark();
    sf::Color btnPrimary = theme.getBtnPrimary();
    sf::Color btnPrimaryHover = theme.getBtnPrimaryHover();
    sf::Color btnSecondary = theme.getBtnSecondary();
    sf::Color btnSecondaryHover = theme.getBtnSecondaryHover();

    //overlay
    auto overlay = tgui::Panel::create();
    overlay->setSize("100%", "100%");
    overlay->getRenderer()->setBackgroundColor(tgui::Color(0, 0, 0, 180));
    gui.add(overlay, "SettingsOverlay");

    //settings dialog
    auto dialog = tgui::Panel::create();
    dialog->setSize(520, 450);
    dialog->setPosition("50%", "50%");
    dialog->setOrigin(0.5f, 0.5f);
    dialog->getRenderer()->setBackgroundColor(tgui::Color(panelBg.r, panelBg.g, panelBg.b));
    dialog->getRenderer()->setBorderColor(tgui::Color(borderColor.r, borderColor.g, borderColor.b));
    dialog->getRenderer()->setBorders(1);
    dialog->getRenderer()->setRoundedBorderRadius(12);
    overlay->add(dialog);

    //title
    auto title = tgui::Label::create();
    title->setText("Settings");
    title->setTextSize(32);
    title->getRenderer()->setTextColor(tgui::Color(textPrimary.r, textPrimary.g, textPrimary.b));
    title->setPosition(40, 40);
    dialog->add(title);

    //divider
    auto divider1 = tgui::Panel::create();
    divider1->setSize(440, 1);
    divider1->setPosition(40, 90);
    divider1->getRenderer()->setBackgroundColor(tgui::Color(dividerColor.r, dividerColor.g, dividerColor.b));
    dialog->add(divider1);

    //theme section label
    auto themeLabel = tgui::Label::create();
    themeLabel->setText("Theme");
    themeLabel->setTextSize(18);
    themeLabel->getRenderer()->setTextColor(tgui::Color(textPrimary.r, textPrimary.g, textPrimary.b));
    themeLabel->setPosition(40, 110);
    dialog->add(themeLabel);

    auto themeDesc = tgui::Label::create();
    themeDesc->setText("Select your preferred color theme");
    themeDesc->setTextSize(14);
    themeDesc->getRenderer()->setTextColor(tgui::Color(textSecondary.r, textSecondary.g, textSecondary.b));
    themeDesc->setPosition(40, 140);
    dialog->add(themeDesc);

    //theme list box (scrollable)
    auto themeListBox = tgui::ListBox::create();
    themeListBox->setSize(440, 140);
    themeListBox->setPosition(40, 170);
    themeListBox->getRenderer()->setBackgroundColor(tgui::Color(panelBg.r, panelBg.g, panelBg.b));
    themeListBox->getRenderer()->setTextColor(tgui::Color(textPrimary.r, textPrimary.g, textPrimary.b));
    themeListBox->getRenderer()->setSelectedBackgroundColor(tgui::Color(btnPrimary.r, btnPrimary.g, btnPrimary.b));
    themeListBox->getRenderer()->setSelectedTextColor(tgui::Color(textOnDark.r, textOnDark.g, textOnDark.b));
    themeListBox->getRenderer()->setBackgroundColorHover(tgui::Color(btnSecondary.r, btnSecondary.g, btnSecondary.b));
    themeListBox->getRenderer()->setTextColorHover(tgui::Color(textPrimary.r, textPrimary.g, textPrimary.b));
    themeListBox->getRenderer()->setBorderColor(tgui::Color(borderColor.r, borderColor.g, borderColor.b));
    themeListBox->getRenderer()->setBorders(1);
    themeListBox->setTextSize(16);
    themeListBox->setItemHeight(45);

    themeListBox->addItem("Classic", "0");
    themeListBox->addItem("Modern", "1");
    themeListBox->addItem("Blue", "2");
    themeListBox->addItem("Dark", "3");
    themeListBox->addItem("Neon Cyberpunk", "4");
    themeListBox->addItem("Sakura", "5");
    themeListBox->addItem("Forest", "6");
    themeListBox->addItem("Sunset", "7");
    themeListBox->addItem("Ocean Deep", "8");
    themeListBox->addItem("Lava", "9");
    themeListBox->addItem("Ice Palace", "10");
    themeListBox->addItem("Retro Arcade", "11");
    themeListBox->addItem("Lavender Dream", "12");
    themeListBox->addItem("Desert Sand", "13");
    themeListBox->addItem("Mint Chocolate", "14");
    themeListBox->addItem("Vampire", "15");
    themeListBox->addItem("Gold Rush", "16");
    themeListBox->addItem("Aurora", "17");
    themeListBox->addItem("Noir", "18");
    themeListBox->addItem("Bubblegum", "19");
    themeListBox->addItem("Toxic", "20");
    themeListBox->addItem("Royal Purple", "21");
    themeListBox->addItem("Matrix", "22");
    

    int selectedIndex = static_cast<int>(selectedThemeType);
    themeListBox->setSelectedItemByIndex(selectedIndex);

    themeListBox->onItemSelect([this](int index) {
        selectedThemeType = static_cast<ThemeType>(index);
        themeChanged = true;
    });

    dialog->add(themeListBox);

    //divider
    auto divider2 = tgui::Panel::create();
    divider2->setSize(440, 1);
    divider2->setPosition(40, 310);
    divider2->getRenderer()->setBackgroundColor(tgui::Color(dividerColor.r, dividerColor.g, dividerColor.b));
    dialog->add(divider2);

    //close button
    auto closeBtn = tgui::Button::create();
    closeBtn->setText("Close");
    closeBtn->setSize(440, 50);
    closeBtn->setPosition(40, 340);
    closeBtn->setTextSize(16);
    closeBtn->getRenderer()->setBackgroundColor(tgui::Color(btnSecondary.r, btnSecondary.g, btnSecondary.b));
    closeBtn->getRenderer()->setBackgroundColorHover(tgui::Color(btnSecondaryHover.r, btnSecondaryHover.g, btnSecondaryHover.b));
    closeBtn->getRenderer()->setBackgroundColorDown(tgui::Color(btnSecondary.r, btnSecondary.g, btnSecondary.b));
    closeBtn->getRenderer()->setTextColor(tgui::Color(textPrimary.r, textPrimary.g, textPrimary.b));
    closeBtn->getRenderer()->setBorderColor(tgui::Color(0, 0, 0, 0));
    closeBtn->getRenderer()->setBorders(0);
    closeBtn->getRenderer()->setRoundedBorderRadius(8);
    closeBtn->onPress([this, overlay] {
        gui.remove(overlay);
    });
    dialog->add(closeBtn);
}



//game ui class


GameUI::GameUI(tgui::Gui& gui, Theme& theme) : gui(gui), theme(theme) {
}


void GameUI::show() {
    //get theme colors
    sf::Color panelBg = theme.getUiPanel();
    sf::Color panelLight = theme.getUiPanelLight();
    sf::Color dividerColor = theme.getUiDivider();
    sf::Color borderColor = theme.getUiBorder();
    sf::Color textPrimary = theme.getTextPrimary();
    sf::Color textSecondary = theme.getTextSecondary();
    sf::Color textAccent = theme.getTextAccent();
    sf::Color textOnDark = theme.getTextOnDark();
    sf::Color btnSecondary = theme.getBtnSecondary();
    sf::Color btnSecondaryHover = theme.getBtnSecondaryHover();
    sf::Color btnPrimary = theme.getBtnPrimary();
    sf::Color btnPrimaryHover = theme.getBtnPrimaryHover();

    //left panel - full height
    auto leftPanel = tgui::Panel::create();
    leftPanel->setSize(400, "100%");
    leftPanel->setPosition(0, 0);
    leftPanel->getRenderer()->setBackgroundColor(tgui::Color(panelBg.r, panelBg.g, panelBg.b));
    gui.add(leftPanel, "LeftPanel");

    //title section
    auto titleLabel = tgui::Label::create();
    titleLabel->setText("CHESS");
    titleLabel->setTextSize(28);
    titleLabel->getRenderer()->setTextColor(tgui::Color(textPrimary.r, textPrimary.g, textPrimary.b));
    titleLabel->setPosition(24, 24);
    leftPanel->add(titleLabel);

    //divider line
    auto divider1 = tgui::Panel::create();
    divider1->setSize(352, 1);
    divider1->setPosition(24, 70);
    divider1->getRenderer()->setBackgroundColor(tgui::Color(dividerColor.r, dividerColor.g, dividerColor.b));
    leftPanel->add(divider1);

    //turn indicator section
    auto turnSectionLabel = tgui::Label::create();
    turnSectionLabel->setText("Current Turn");
    turnSectionLabel->setTextSize(14);
    turnSectionLabel->getRenderer()->setTextColor(tgui::Color(textSecondary.r, textSecondary.g, textSecondary.b));
    turnSectionLabel->setPosition(24, 90);
    leftPanel->add(turnSectionLabel);

    turnLabel = tgui::Label::create();
    turnLabel->setText("White");
    turnLabel->setTextSize(24);
    turnLabel->getRenderer()->setTextColor(tgui::Color(textPrimary.r, textPrimary.g, textPrimary.b));
    turnLabel->setPosition(24, 112);
    leftPanel->add(turnLabel);

    //status section
    statusLabel = tgui::Label::create();
    statusLabel->setText("");
    statusLabel->setTextSize(16);
    statusLabel->getRenderer()->setTextColor(tgui::Color(textAccent.r, textAccent.g, textAccent.b));
    statusLabel->setPosition(24, 148);
    leftPanel->add(statusLabel);

    //divider line
    auto divider2 = tgui::Panel::create();
    divider2->setSize(352, 1);
    divider2->setPosition(24, 180);
    divider2->getRenderer()->setBackgroundColor(tgui::Color(dividerColor.r, dividerColor.g, dividerColor.b));
    leftPanel->add(divider2);

    //move history section
    auto historyLabel = tgui::Label::create();
    historyLabel->setText("Move History");
    historyLabel->setTextSize(14);
    historyLabel->getRenderer()->setTextColor(tgui::Color(textSecondary.r, textSecondary.g, textSecondary.b));
    historyLabel->setPosition(24, 200);
    leftPanel->add(historyLabel);

    //move history list box
    moveHistoryList = tgui::ListBox::create();
    moveHistoryList->setSize(352, 340);
    moveHistoryList->setPosition(24, 228);
    moveHistoryList->getRenderer()->setBackgroundColor(tgui::Color(panelLight.r, panelLight.g, panelLight.b));
    moveHistoryList->getRenderer()->setTextColor(tgui::Color(textPrimary.r, textPrimary.g, textPrimary.b));
    moveHistoryList->getRenderer()->setSelectedBackgroundColor(tgui::Color(btnPrimary.r, btnPrimary.g, btnPrimary.b));
    moveHistoryList->getRenderer()->setSelectedTextColor(tgui::Color(textOnDark.r, textOnDark.g, textOnDark.b));
    moveHistoryList->getRenderer()->setBorderColor(tgui::Color(borderColor.r, borderColor.g, borderColor.b));
    moveHistoryList->getRenderer()->setBorders(1);
    moveHistoryList->setTextSize(13);
    leftPanel->add(moveHistoryList);

    //divider line
    auto divider3 = tgui::Panel::create();
    divider3->setSize(352, 1);
    divider3->setPosition(24, 585);
    divider3->getRenderer()->setBackgroundColor(tgui::Color(dividerColor.r, dividerColor.g, dividerColor.b));
    leftPanel->add(divider3);

    //navigation controls section
    auto navLabel = tgui::Label::create();
    navLabel->setText("Navigation");
    navLabel->setTextSize(14);
    navLabel->getRenderer()->setTextColor(tgui::Color(textSecondary.r, textSecondary.g, textSecondary.b));
    navLabel->setPosition(24, 603);
    leftPanel->add(navLabel);

    //navigation buttons
    auto styleNavButton = [btnSecondary, btnSecondaryHover, textPrimary](tgui::Button::Ptr btn) {
        btn->getRenderer()->setBackgroundColor(tgui::Color(btnSecondary.r, btnSecondary.g, btnSecondary.b));
        btn->getRenderer()->setBackgroundColorHover(tgui::Color(btnSecondaryHover.r, btnSecondaryHover.g, btnSecondaryHover.b));
        btn->getRenderer()->setBackgroundColorDown(tgui::Color(btnSecondary.r, btnSecondary.g, btnSecondary.b));
        btn->getRenderer()->setTextColor(tgui::Color(textPrimary.r, textPrimary.g, textPrimary.b));
        btn->getRenderer()->setBorderColor(tgui::Color(0, 0, 0, 0));
        btn->getRenderer()->setBorders(0);
        btn->getRenderer()->setRoundedBorderRadius(6);
        btn->setTextSize(13);
    };

    firstMoveButton = tgui::Button::create();
    firstMoveButton->setText("|<");
    firstMoveButton->setSize(80, 38);
    firstMoveButton->setPosition(24, 630);
    styleNavButton(firstMoveButton);
    leftPanel->add(firstMoveButton);

    prevMoveButton = tgui::Button::create();
    prevMoveButton->setText("<");
    prevMoveButton->setSize(80, 38);
    prevMoveButton->setPosition(114, 630);
    styleNavButton(prevMoveButton);
    leftPanel->add(prevMoveButton);

    nextMoveButton = tgui::Button::create();
    nextMoveButton->setText(">");
    nextMoveButton->setSize(80, 38);
    nextMoveButton->setPosition(204, 630);
    styleNavButton(nextMoveButton);
    leftPanel->add(nextMoveButton);

    lastMoveButton = tgui::Button::create();
    lastMoveButton->setText(">|");
    lastMoveButton->setSize(82, 38);
    lastMoveButton->setPosition(294, 630);
    styleNavButton(lastMoveButton);
    leftPanel->add(lastMoveButton);

    //menu button
    menuButton = tgui::Button::create();
    menuButton->setText("Main Menu");
    menuButton->setSize(352, 48);
    menuButton->setPosition(24, 688);
    menuButton->setTextSize(15);
    menuButton->getRenderer()->setBackgroundColor(tgui::Color(btnPrimary.r, btnPrimary.g, btnPrimary.b));
    menuButton->getRenderer()->setBackgroundColorHover(tgui::Color(btnPrimaryHover.r, btnPrimaryHover.g, btnPrimaryHover.b));
    menuButton->getRenderer()->setBackgroundColorDown(tgui::Color(btnPrimary.r, btnPrimary.g, btnPrimary.b));
    menuButton->getRenderer()->setTextColor(tgui::Color(textOnDark.r, textOnDark.g, textOnDark.b));
    menuButton->getRenderer()->setRoundedBorderRadius(8);
    menuButton->getRenderer()->setBorderColor(tgui::Color(0, 0, 0, 0));
    menuButton->getRenderer()->setBorders(0);
    leftPanel->add(menuButton);
}


void GameUI::hide() {
    gui.remove(gui.get("LeftPanel"));
}

void GameUI::updateTurn(const std::string &color) {
    if(turnLabel) turnLabel->setText(color);
}

void GameUI::updateStatus(const std::string &status) {
    if(statusLabel) statusLabel->setText(status);
}

void GameUI::addMoveToHistory(const std::string &move) {
    if(moveHistoryList) {
        moveHistoryList->addItem(move);
        //auto-scroll to bottom
        if(moveHistoryList->getItemCount() > 0) {
            moveHistoryList->setSelectedItemByIndex(moveHistoryList->getItemCount() - 1);
        }
    }
}

void GameUI::clearMoveHistory() {
    if(moveHistoryList) {
        moveHistoryList->removeAllItems();
    }
}

void GameUI::setMenuCallback(std::function<void ()> callback) {
    onMenuPressed = callback;
    if(menuButton) {
        menuButton->onPress(callback);
    }
}

void GameUI::setNavigationCallbacks(
    std::function<void()> onFirst,
    std::function<void()> onPrev,
    std::function<void()> onNext,
    std::function<void()> onLast
) {
    if(firstMoveButton) firstMoveButton->onPress(onFirst);
    if(prevMoveButton) prevMoveButton->onPress(onPrev);
    if(nextMoveButton) nextMoveButton->onPress(onNext);
    if(lastMoveButton) lastMoveButton->onPress(onLast);
}


void GameUI::showGameOverDialog(const std::string &message, std::function<void ()> onRestart, std::function<void ()> onQuit) {
    //get theme colors
    sf::Color panelBg = theme.getUiPanel();
    sf::Color borderColor = theme.getUiBorder();
    sf::Color textPrimary = theme.getTextPrimary();
    sf::Color textSecondary = theme.getTextSecondary();
    sf::Color textOnDark = theme.getTextOnDark();
    sf::Color btnSuccess = theme.getBtnSuccess();
    sf::Color btnSuccessHover = theme.getBtnSuccessHover();
    sf::Color btnSecondary = theme.getBtnSecondary();
    sf::Color btnSecondaryHover = theme.getBtnSecondaryHover();

    //overlay
    auto overlay = tgui::Panel::create();
    overlay->setSize("100%", "100%");
    overlay->getRenderer()->setBackgroundColor(tgui::Color(0, 0, 0, 180));
    gui.add(overlay);


    auto dialog = tgui::Panel::create();
    dialog->setSize(480, 320);
    dialog->setPosition("50%", "50%");
    dialog->setOrigin(0.5f, 0.5f);
    dialog->getRenderer()->setBackgroundColor(tgui::Color(panelBg.r, panelBg.g, panelBg.b));
    dialog->getRenderer()->setBorderColor(tgui::Color(borderColor.r, borderColor.g, borderColor.b));
    dialog->getRenderer()->setBorders(1);
    dialog->getRenderer()->setRoundedBorderRadius(12);
    overlay->add(dialog);

    auto title = tgui::Label::create();
    title->setText("Game Over");
    title->setTextSize(32);
    title->getRenderer()->setTextColor(tgui::Color(textPrimary.r, textPrimary.g, textPrimary.b));
    title->setPosition("50%", 40);
    title->setOrigin(0.5f, 0.0f);
    dialog->add(title);


    auto msgLabel = tgui::Label::create();
    msgLabel->setText(message);
    msgLabel->setTextSize(20);
    msgLabel->getRenderer()->setTextColor(tgui::Color(textSecondary.r, textSecondary.g, textSecondary.b));
    msgLabel->setPosition("50%", 100);
    msgLabel->setOrigin(0.5f, 0.0f);
    msgLabel->setHorizontalAlignment(tgui::HorizontalAlignment::Center);
    dialog->add(msgLabel);

    //restart
    auto restartBtn = tgui::Button::create();
    restartBtn->setText("Play Again");
    restartBtn->setSize(380, 55);
    restartBtn->setPosition("50%", 160);
    restartBtn->setOrigin(0.5f, 0.0f);
    restartBtn->setTextSize(16);
    restartBtn->getRenderer()->setBackgroundColor(tgui::Color(btnSuccess.r, btnSuccess.g, btnSuccess.b));
    restartBtn->getRenderer()->setBackgroundColorHover(tgui::Color(btnSuccessHover.r, btnSuccessHover.g, btnSuccessHover.b));
    restartBtn->getRenderer()->setBackgroundColorDown(tgui::Color(btnSuccess.r, btnSuccess.g, btnSuccess.b));
    restartBtn->getRenderer()->setTextColor(tgui::Color(textOnDark.r, textOnDark.g, textOnDark.b));
    restartBtn->getRenderer()->setBorderColor(tgui::Color(0, 0, 0, 0));
    restartBtn->getRenderer()->setBorders(0);
    restartBtn->getRenderer()->setRoundedBorderRadius(8);
    restartBtn->onPress([this, onRestart, overlay] {
        gui.remove(overlay);
        onRestart();
    });
    dialog->add(restartBtn);


    //menu button
    auto quitBtn = tgui::Button::create();
    quitBtn->setText("Main Menu");
    quitBtn->setSize(380, 50);
    quitBtn->setPosition("50%", 230);
    quitBtn->setOrigin(0.5f, 0.0f);
    quitBtn->setTextSize(16);
    quitBtn->getRenderer()->setBackgroundColor(tgui::Color(btnSecondary.r, btnSecondary.g, btnSecondary.b));
    quitBtn->getRenderer()->setBackgroundColorHover(tgui::Color(btnSecondaryHover.r, btnSecondaryHover.g, btnSecondaryHover.b));
    quitBtn->getRenderer()->setBackgroundColorDown(tgui::Color(btnSecondary.r, btnSecondary.g, btnSecondary.b));
    quitBtn->getRenderer()->setTextColor(tgui::Color(textPrimary.r, textPrimary.g, textPrimary.b));
    quitBtn->getRenderer()->setBorderColor(tgui::Color(0, 0, 0, 0));
    quitBtn->getRenderer()->setBorders(0);
    quitBtn->getRenderer()->setRoundedBorderRadius(8);
    quitBtn->onPress([this, onQuit, overlay] {
        gui.remove(overlay);
        onQuit();
    });
    dialog->add(quitBtn);

}

