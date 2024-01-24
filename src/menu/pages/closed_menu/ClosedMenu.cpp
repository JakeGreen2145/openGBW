#include "ClosedMenu.hpp"


// TODO: update all constructors to pull from preferences first
ClosedMenu::ClosedMenu() {
    menuPreferences.begin("scale", false);
    double initialValue = menuPreferences.getDouble("setWeight", (double)COFFEE_DOSE_WEIGHT);
    menuPreferences.end();
    this -> value = initialValue;
    this -> name = "Closed Menu";
    this -> menuId = NONE;
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

void ClosedMenu::setValue(double newValue) {
    this->value = newValue;
    menuPreferences.begin("scale", false);
    menuPreferences.putDouble("setWeight", newValue);
    Serial.print("New set weight set to: ");
    Serial.println(newValue);
    menuPreferences.end();
}

void ClosedMenu::handleEncoderChange(int encoderDelta) {
    double newValue = value + ((float)encoderDelta) / 10;
    setValue(newValue);
}

void ClosedMenu::handleEncoderClick(AiEsp32RotaryEncoder rotaryEncoder) {
    rotaryEncoder.setAcceleration(0);
    DeviceState::setGrinderState(STATUS_IN_MENU);
    DeviceState::setActiveMenu(MAIN_MENU);
}