#include "MainMenu.hpp"


MainMenu::MainMenu(MenuId initialValue, std::string name, MenuId menuId){
    this -> value = initialValue;
    this -> name = name;
    this -> menuId = menuId;
};

MainMenu& MainMenu::getMainMenu(MenuId initialValue, std::string name, MenuId menuId) {
    instance = MainMenu(initialValue, name, menuId);
    return instance;
}

// implementation for displayMenu and increment
void MainMenu::displayMenu() {
    // set current menu to active
    setActiveMenu(menuId);
    // set global variables
    // TODO: move away from these
    
}

void MainMenu::incrementValue(MenuId increment) {
    //value += increment;
}

void MainMenu::handleEncoderChange(int encoderValue, int encoderDirection) {
    int newValue = rotaryEncoder.readEncoder();
    currentMenuItem = (currentMenuItem + (newValue - encoderValue) * encoderDirection) % menuItemsCount;
    // TODO: change display to use activeMenu instead of currentMenuItem
    currentMenuItem = currentMenuItem < 0 ? menuItemsCount + currentMenuItem : currentMenuItem;
    this -> encoderValue = newValue;
    Serial.println(currentMenuItem);
}

void MainMenu::handleEncoderClick() {
    if(value == EXIT){
        setActiveMenu(NONE);
        grinderState = STATUS_EMPTY;
        rotaryEncoder.setAcceleration(100);
        Serial.println("Exited Menu");
    }
    else if (value == OFFSET){
        setActiveMenu(OFFSET);
        grinderState = STATUS_IN_SUBMENU;
        currentSetting = getActiveMenu();
        Serial.println("Offset Menu");
    }
    else if (value == CUP_WEIGHT_MENU)
    {
        setActiveMenu(CUP_WEIGHT_MENU);
        grinderState = STATUS_IN_SUBMENU;
        currentSetting = getActiveMenu();
        Serial.println("Cup Menu");
    }
    else if (value == CALIBRATE)
    {
        setActiveMenu(CALIBRATE);
        grinderState = STATUS_IN_SUBMENU;
        currentSetting = getActiveMenu();
        Serial.println("Calibration Menu");
    }
    else if (value == SCALE_MODE)
    {
        setActiveMenu(SCALE_MODE);
        grinderState = STATUS_IN_SUBMENU;
        currentSetting = getActiveMenu();
        Serial.println("Scale Mode Menu");
    }
    else if (value == GRINDING_MODE)
    {
        setActiveMenu(GRINDING_MODE);
        grinderState = STATUS_IN_SUBMENU;
        currentSetting = getActiveMenu();
        Serial.println("Grind Mode Menu");
    }
    else if (value == RESET)
    {
        setActiveMenu(RESET);
        grinderState = STATUS_IN_SUBMENU;
        currentSetting = getActiveMenu();
        greset = false;
        Serial.println("Reset Menu");
    }
}