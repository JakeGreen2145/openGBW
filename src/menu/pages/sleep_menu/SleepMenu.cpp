#include "SleepMenu.hpp"


SleepMenu::SleepMenu() {
    menuPreferences.begin("scale", false);
    double initialValue = menuPreferences.getLong("sleepTimeout", (long)SLEEP_AFTER_MS);
    menuPreferences.end();
    this -> value = initialValue;
    this -> name = "Sleep Timeout Menu";
    this -> menuId = SLEEP;
};

SleepMenu SleepMenu::instance = SleepMenu();

SleepMenu& SleepMenu::getSleepMenu() {
    return instance;
}

void SleepMenu::displayMenu(U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2) {
    // set current menu to active
    // setActiveMenu(menuId);
    // set global variables
    // TODO: move away from these
}

void SleepMenu::handleEncoderChange(int encoderDelta) {
    encoderDelta *= 1000; // convert to milliseconds
    long newValue = value + encoderDelta;
    setValue(newValue);
}

void SleepMenu::setValue(double newValue) {
    this->value = newValue;
    menuPreferences.begin("scale", false);
    menuPreferences.putDouble("sleepTimeout", newValue);
    Serial.print("New sleep timeout was set to: ");
    Serial.println(newValue);
    menuPreferences.end();
}

void SleepMenu::handleEncoderClick(AiEsp32RotaryEncoder rotaryEncoder) {
    DeviceState::setActiveMenu(MAIN_MENU);
    DeviceState::setGrinderState(STATUS_IN_MENU);
}
