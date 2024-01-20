#include "MainMenu.hpp"
#include <vector>

std::vector<int> mainMenuOptions = {
    EXIT, CALIBRATE, CUP_WEIGHT_MENU, OFFSET, SCALE_MODE, GRINDING_MODE, SLEEP, RESET
};

// TODO: find a better solution for this that stays in sync with the options above
std::vector<char*> mainMenuNames = {
    "Exit", "Calibrate Scale", "Set Cup Weight", "Set Offset", "Set Scale Mode", "Set Grind Mode", "Set Sleep Timeout", "Reset Settings"
};

int menuItemsCount = mainMenuOptions.size();

MainMenu::MainMenu(){
    this -> value = EXIT;
    this -> name = "Main Menu";
    this -> menuId = MAIN_MENU;
};

MainMenu& MainMenu::getMainMenu() {
    instance = MainMenu();
    return instance;
}

const char* MainMenu::getSelectedMenuName() {
    return mainMenuNames.at(menuIndex);
}

const char* MainMenu::getNextMenuName() {
    int nextIndex = (menuIndex + 1) % menuItemsCount;
    return mainMenuNames.at(nextIndex);
}

const char* MainMenu::getPrevMenuName() {
    int prevIndex = (menuIndex - 1) % menuItemsCount;
    prevIndex = prevIndex < 0 ? prevIndex + menuItemsCount : prevIndex;
    return mainMenuNames.at(prevIndex);
}



// implementation for displayMenu and increment
void MainMenu::displayMenu(U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2) {
    // int prevIndex = (menuIndex - 1) % menuItemsCount;
    // int nextIndex = (menuIndex + 1) % menuItemsCount;

    // prevIndex = prevIndex < 0 ? prevIndex + menuItemsCount : prevIndex;
    // MenuId prev = static_cast<MenuId>(mainMenuOptions.at(prevIndex));
    // MenuId current = static_cast<MenuId>(mainMenuOptions.at(menuIndex));
    // MenuId next = static_cast<MenuId>(mainMenuOptions.at(nextIndex));
    // char buf[3];
    // u8g2.clearBuffer();
    // u8g2.setFontPosTop();
    // u8g2.setFont(u8g2_font_7x14B_tf);
    // CenterPrintToScreen("Menu", 0);
    // u8g2.setFont(u8g2_font_7x13_tr);
    // LeftPrintToScreen(prev.menuName, 19);
    // LeftPrintActiveToScreen(current.menuName, 35);
    // LeftPrintToScreen(next.menuName, 51);

    // u8g2.sendBuffer();
    
}

void MainMenu::incrementValue(MenuId increment) {
    // prevent array out of bounds
    menuIndex = (menuIndex + increment) % menuItemsCount;
    // loop menu
    menuIndex = menuIndex < 0 ? menuItemsCount + menuIndex : menuIndex;
    value = static_cast<MenuId>(mainMenuOptions.at(menuIndex));
}

// TODO: remove this or remove the increment function above
void MainMenu::handleEncoderChange(int encoderDelta) {
    // prevent array out of bounds
    menuIndex = (menuIndex + encoderDelta) % menuItemsCount;
    // loop menu
    menuIndex = menuIndex < 0 ? menuItemsCount + menuIndex : menuIndex;
    value = static_cast<MenuId>(mainMenuOptions.at(menuIndex));
}

void MainMenu::handleEncoderClick(AiEsp32RotaryEncoder rotaryEncoder) {
    if(value == EXIT){
        activeMenu = NONE;
        grinderState = STATUS_EMPTY;
        rotaryEncoder.setAcceleration(100);
        Serial.println("Exited Menu");
    }
    else if (value == OFFSET){
        activeMenu = OFFSET;
        grinderState = STATUS_IN_SUBMENU;
        Serial.println("Offset Menu");
    }
    else if (value == CUP_WEIGHT_MENU)
    {
        activeMenu = CUP_WEIGHT_MENU;
        grinderState = STATUS_IN_SUBMENU;
        Serial.println("Cup Menu");
    }
    else if (value == CALIBRATE)
    {
        activeMenu = CALIBRATE;
        grinderState = STATUS_IN_SUBMENU;
        Serial.println("Calibration Menu");
    }
    else if (value == SCALE_MODE)
    {
        activeMenu = SCALE_MODE;
        grinderState = STATUS_IN_SUBMENU;
        Serial.println("Scale Mode Menu");
    }
    else if (value == GRINDING_MODE)
    {
        activeMenu = GRINDING_MODE;
        grinderState = STATUS_IN_SUBMENU;
        Serial.println("Grind Mode Menu");
    }
    else if (value == RESET)
    {
        activeMenu = RESET;
        grinderState = STATUS_IN_SUBMENU;
        //greset = false;
        Serial.println("Reset Menu");
    }
}