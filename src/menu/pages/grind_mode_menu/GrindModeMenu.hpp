#pragma once

#include "../Menu.hpp"
#include <string>

// Menu for adjusting the grind weight offset
class GrindModeMenu : public Menu<bool> {
    private:
        // private constructor for singleton
        GrindModeMenu();
        static GrindModeMenu instance;

    public:

        // Accessor
        static GrindModeMenu& getGrindModeMenu();

        void displayMenu(U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2) override;

        void handleEncoderChange(int encoderDelta) override;

        void handleEncoderClick(AiEsp32RotaryEncoder encoder) override;

        void setValue(bool newValue);
};
