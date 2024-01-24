#include "GrindModeMenu.hpp"


GrindModeMenu::GrindModeMenu() {
    menuPreferences.begin("scale", false);
    bool initialValue = menuPreferences.getBool("grindMode", false);
    menuPreferences.end();
    this -> value = initialValue;
    this -> name = "Grind Mode Menu";
    this -> menuId = GRINDING_MODE;
};

GrindModeMenu GrindModeMenu::instance = GrindModeMenu();

GrindModeMenu& GrindModeMenu::getGrindModeMenu() {
    return instance;
}

// implementation for displayMenu and increment
void GrindModeMenu::displayMenu(U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2) {
    // set current menu to active
    // setActiveMenu(menuId);
    // set global variables
    // TODO: move away from these
}

void GrindModeMenu::handleEncoderChange(int encoderDelta) {
    // toggle the value. Don't save the setting until the encoder click
    value = !value;
}

void GrindModeMenu::setValue(bool newValue) {
    this->value = newValue;
    menuPreferences.begin("scale", false);
    menuPreferences.putBool("grindMode", newValue);
    Serial.print("GrindMode set to: ");
    Serial.println(newValue);
    menuPreferences.end();
}

void GrindModeMenu::handleEncoderClick(AiEsp32RotaryEncoder rotaryEncoder) {
    setValue(value); // Save current preference;
    DeviceState::setGrinderState(STATUS_IN_MENU);
    DeviceState::setActiveMenu(MAIN_MENU);
}
