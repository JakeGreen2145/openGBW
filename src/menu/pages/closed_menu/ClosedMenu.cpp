#include "ClosedMenu.hpp"


Preferences controllerPreferences;

ClosedMenu::ClosedMenu(){
    this -> value = NONE;
    this -> name = "Closed Menu";
    this -> menuId = MAIN_MENU;
};

ClosedMenu& ClosedMenu::getClosedMenu() {
    instance = ClosedMenu();
    return instance;
}

// implementation for displayMenu and increment
void ClosedMenu::displayMenu(U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2) {
    // set current menu to active
    // setActiveMenu(menuId);
    // set global variables
    // TODO: move away from these
}

void ClosedMenu::incrementValue(double increment) {
    // remove me
}

// TODO: remove this or remove the increment function above
void ClosedMenu::handleEncoderChange(int encoderDelta) {
    Serial.print("Value: ");
    value += ((float)encoderDelta) / 10;
    Serial.println(value);
    controllerPreferences.begin("scale", false);
    controllerPreferences.putDouble("setWeight", value);
    controllerPreferences.end();
}

void ClosedMenu::handleEncoderClick(AiEsp32RotaryEncoder rotaryEncoder) {
    Menu<void*>::setGrinderState(STATUS_IN_MENU);
    rotaryEncoder.setAcceleration(0);
    setActiveMenu(MAIN_MENU);
}