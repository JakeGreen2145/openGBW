#pragma once

#include <Preferences.h>
#include <string>
#include <AiEsp32RotaryEncoder.h>
#include <U8g2lib.h>

#include "../DeviceState.hpp"

#define CUP_WEIGHT 70
#define CUP_DETECTION_TOLERANCE 5 // 5 grams tolerance above or bellow cup weight to detect it

#define LOADCELL_DOUT_PIN 19
#define LOADCELL_SCK_PIN 18

#define LOADCELL_SCALE_FACTOR 7351

#define TARE_MEASURES 20 // use the average of measure for taring
#define SIGNIFICANT_WEIGHT_CHANGE 5 // 5 grams changes are used to detect a significant change
#define COFFEE_DOSE_WEIGHT 18
#define COFFEE_DOSE_OFFSET -2.5
#define MAX_GRINDING_TIME 20000 // 20 seconds diff
#define GRINDING_FAILED_WEIGHT_TO_RESET 150 // force on balance need to be measured to reset grinding
#define SLEEP_AFTER_MS 60 * 1000 // sleep after 60 seconds by default

#define GRINDER_ACTIVE_PIN 33

#define TARE_MIN_INTERVAL 10 * 1000 // auto-tare at most once every 10 seconds

#define ROTARY_ENCODER_A_PIN 32
#define ROTARY_ENCODER_B_PIN 23
#define ROTARY_ENCODER_BUTTON_PIN 34
#define ROTARY_ENCODER_VCC_PIN -1
#define ROTARY_ENCODER_STEPS 4

class BaseMenu {
    // Define menu methods here that are independent of the value type.
    protected:
        std::string name;
        MenuId menuId;
        Preferences menuPreferences; // Writes settings to disk for non-volatile behavior
    public:
        // Display the menu options
        virtual void displayMenu(U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2) = 0;

        // Interaction
        virtual void handleEncoderChange(int encoderDelta) = 0;
        virtual void handleEncoderClick(AiEsp32RotaryEncoder encoder) = 0;

        // Virtual destructor (important for polymorphic behavior)
        virtual ~BaseMenu() {};
};



template <typename T>
class Menu : public BaseMenu {
    protected:
        T value;
    public:
        // Setters
        void setValue(T newValue);

        // Getters
        T getValue() const;

        // Virtual destructor
        virtual ~Menu() {};
};


// ------- Setters -------
template <typename T>
void Menu<T>::setValue(T newValue) {
    value = newValue;
}


// ------- Getters ------- 
template <typename T>
T Menu<T>::getValue() const {
    return value;
}