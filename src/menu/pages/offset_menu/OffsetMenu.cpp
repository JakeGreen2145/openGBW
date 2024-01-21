#include "OffsetMenu.hpp"


Preferences controllerPreferences;

OffsetMenu::OffsetMenu(){
    this -> value = NONE;
    this -> name = "Closed Menu";
    this -> menuId = MAIN_MENU;
};

OffsetMenu OffsetMenu::instance = OffsetMenu();

OffsetMenu& OffsetMenu::getOffsetMenu() {
    return instance;
}

// implementation for displayMenu and increment
void OffsetMenu::displayMenu(U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2) {
    // set current menu to active
    // setActiveMenu(menuId);
    // set global variables
    // TODO: move away from these
}

// TODO: remove this or remove the increment function above
void OffsetMenu::handleEncoderChange(int encoderDelta) {
    Serial.print("Value: ");
    value += ((float)encoderDelta) / 100;
    if(abs(value) >= setWeight) {
        offset = setWeight;     //prevent nonsensical offsets
    }
}

void OffsetMenu::handleEncoderClick(AiEsp32RotaryEncoder rotaryEncoder) {
    controllerPreferences.begin("scale", false);
    controllerPreferences.putDouble("offset", getValue());
    controllerPreferences.end();
    DeviceState::setGrinderState(STATUS_IN_MENU);
    DeviceState::setActiveMenu(MAIN_MENU);
}