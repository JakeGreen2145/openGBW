#include "CupMenu.hpp"


CupMenu::CupMenu() {
    menuPreferences.begin("scale", false);
    double initialValue = menuPreferences.getDouble("cup", (double)CUP_WEIGHT);
    menuPreferences.end();
    this -> value = initialValue;
    this -> name = "Cup Menu";
    this -> menuId = CUP_WEIGHT_MENU;
};

CupMenu CupMenu::instance = CupMenu();

CupMenu& CupMenu::getCupMenu() {
    return instance;
}

void CupMenu::displayMenu(U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2) {
    // set current menu to active
    // setActiveMenu(menuId);
    // set global variables
    // TODO: move away from these
}

void CupMenu::handleEncoderChange(int encoderDelta) {
    // no op
}

void CupMenu::setValue(double newValue) {
    this->value = newValue;
    menuPreferences.begin("scale", false);
    menuPreferences.putDouble("cup", newValue);
    Serial.print("New cup weight was set to: ");
    Serial.println(newValue);
    menuPreferences.end();
}

void CupMenu::handleEncoderClick(AiEsp32RotaryEncoder rotaryEncoder) {
    //prevent accidental setting with no cup
    double scaleWeight = kalmanFilter.updateEstimate(loadcell.get_units(5));
    if(scaleWeight > 30) {
        setValue(scaleWeight);
    } else {
        Serial.println("Cup weight was under 30. New cup weight not set.");
    }
    DeviceState::setActiveMenu(MAIN_MENU);
    DeviceState::setGrinderState(STATUS_IN_MENU);
}
