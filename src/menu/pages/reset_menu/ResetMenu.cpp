#include "ResetMenu.hpp"


ResetMenu::ResetMenu() {
    this -> value = false;
    this -> name = "Reset Menu";
    this -> menuId = RESET;
};

ResetMenu ResetMenu::instance = ResetMenu();

ResetMenu& ResetMenu::getResetMenu() {
    return instance;
}

// implementation for displayMenu and increment
void ResetMenu::displayMenu(U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2) {
    // set current menu to active
    // setActiveMenu(menuId);
    // set global variables
    // TODO: move away from these
}

// toggle value, but don't change preferences until the user confirms via encoder click
void ResetMenu::handleEncoderChange(int encoderDelta) {
    value = !value;
}

// reset logic is handled in the controller to defer setting changes to other menus
void ResetMenu::handleEncoderClick(AiEsp32RotaryEncoder rotaryEncoder) {
    // no-op
}