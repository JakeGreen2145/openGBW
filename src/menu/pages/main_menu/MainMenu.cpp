#include "MainMenu.hpp"
#include <vector> 

std::vector<int> mainMenuOptions = {
    EXIT, CALIBRATE, CUP_WEIGHT_MENU, OFFSET, SCALE_MODE, GRINDING_MODE, SLEEP, RESET
};

// TODO: find a better solution for this that stays in sync with the options above
std::vector<const char*> mainMenuNames = {
    "Exit", "Calibrate Scale", "Set Cup Weight", "Set Offset", "Set Scale Mode", "Set Grind Mode", "Set Sleep Timeout", "Reset Settings"
};

int menuItemsCount = mainMenuOptions.size();

MainMenu::MainMenu(){
    this -> value = EXIT;
    this -> name = "Main Menu";
    this -> menuId = MAIN_MENU;
};

MainMenu MainMenu::instance = MainMenu();

MainMenu& MainMenu::getMainMenu() {
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

void MainMenu::handleEncoderChange(int encoderDelta) {
    // prevent array out of bounds
    menuIndex = (menuIndex + encoderDelta) % menuItemsCount;
    // loop menu
    menuIndex = menuIndex < 0 ? menuItemsCount + menuIndex : menuIndex;
    value = static_cast<MenuId>(mainMenuOptions.at(menuIndex));
}

void MainMenu::handleEncoderClick(AiEsp32RotaryEncoder rotaryEncoder) {
    if(value == EXIT){
        DeviceState::setActiveMenu(NONE);
        DeviceState::setGrinderState(STATUS_EMPTY);
        rotaryEncoder.setAcceleration(100);
        Serial.println("Exited Menu");
    }
    else if (value == OFFSET){
        DeviceState::setActiveMenu(OFFSET);
        DeviceState::setGrinderState(STATUS_IN_SUBMENU);
        Serial.println("Offset Menu");
    }
    else if (value == CUP_WEIGHT_MENU)
    {
        DeviceState::setActiveMenu(CUP_WEIGHT_MENU);
        DeviceState::setGrinderState(STATUS_IN_SUBMENU);
        Serial.println("Cup Menu");
    }
    else if (value == CALIBRATE)
    {
        DeviceState::setActiveMenu(CALIBRATE);
        DeviceState::setGrinderState(STATUS_IN_SUBMENU);
        Serial.println("Calibration Menu");
    }
    else if (value == SCALE_MODE)
    {
        DeviceState::setActiveMenu(SCALE_MODE);
        DeviceState::setGrinderState(STATUS_IN_SUBMENU);
        Serial.println("Scale Mode Menu");
    }
    else if (value == GRINDING_MODE)
    {
        DeviceState::setActiveMenu(GRINDING_MODE);
        DeviceState::setGrinderState(STATUS_IN_SUBMENU);
        Serial.println("Grind Mode Menu");
    }
    else if (value == RESET)
    {
        DeviceState::setActiveMenu(RESET);
        DeviceState::setGrinderState(STATUS_IN_SUBMENU);
        Serial.println("Reset Menu");
    }
    else if (value == SLEEP)
    {
        DeviceState::setActiveMenu(SLEEP);
        DeviceState::setGrinderState(STATUS_IN_SUBMENU);
        Serial.println("Sleep Timeout Menu");
    }
}