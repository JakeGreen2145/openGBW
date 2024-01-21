#include "ClosedMenu.hpp"


Preferences controllerPreferences;

ClosedMenu::ClosedMenu(){
    this -> value = 18.0;
    this -> name = "Closed Menu";
    this -> menuId = MAIN_MENU;
};

ClosedMenu ClosedMenu::instance = ClosedMenu();

ClosedMenu& ClosedMenu::getClosedMenu() {
    return instance;
}

// implementation for displayMenu and increment
void ClosedMenu::displayMenu(U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2) {
    // set current menu to active
    // setActiveMenu(menuId);
    // set global variables
    // TODO: move away from these
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
    DeviceState::setGrinderState(STATUS_IN_MENU);
    rotaryEncoder.setAcceleration(0);
    DeviceState::setActiveMenu(MAIN_MENU);
}