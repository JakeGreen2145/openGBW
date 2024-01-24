#pragma once

#include "../Menu.hpp"
#include <string>

// Menu for toggling the scale mode
class ScaleModeMenu : public Menu<bool> {
    private:
        // private constructor for singleton
        ScaleModeMenu();
        static ScaleModeMenu instance;

    public:

        // Accessor
        static ScaleModeMenu& getScaleModeMenu();

        void displayMenu(U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2) override;

        void handleEncoderChange(int encoderDelta) override;

        void handleEncoderClick(AiEsp32RotaryEncoder encoder) override;

        void setValue(bool newValue);
};
