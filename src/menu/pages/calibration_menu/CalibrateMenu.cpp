#include "CalibrateMenu.hpp"


CalibrateMenu::CalibrateMenu() {
    menuPreferences.begin("scale", false);
    double initialValue = menuPreferences.getDouble("calibration", (double)LOADCELL_SCALE_FACTOR);
    menuPreferences.end();
    this -> value = initialValue;
    this -> name = "Calibrate Menu";
    this -> menuId = CALIBRATE;
};

CalibrateMenu CalibrateMenu::instance = CalibrateMenu();

CalibrateMenu& CalibrateMenu::getCalibrateMenu() {
    return instance;
}

// implementation for displayMenu and increment
void CalibrateMenu::displayMenu(U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2) {
    // set current menu to active
    // setActiveMenu(menuId);
    // set global variables
    // TODO: move away from these
}

void CalibrateMenu::handleEncoderChange(int encoderDelta) {
    // no op
}

void CalibrateMenu::setValue(double newValue) {
    this->value = newValue;
    menuPreferences.begin("scale", false);
    menuPreferences.putDouble("calibration", newValue);
    Serial.print("New scale factor set to: ");
    Serial.println(newValue);
    menuPreferences.end();
}

void CalibrateMenu::handleEncoderClick(AiEsp32RotaryEncoder rotaryEncoder) {
    double scaleWeight = kalmanFilter.updateEstimate(loadcell.get_units(5));
    double newCalibrationValue = value * (scaleWeight / 100);

    setValue(newCalibrationValue);
    DeviceState::setGrinderState(STATUS_IN_MENU);
    DeviceState::setActiveMenu(MAIN_MENU);

}
