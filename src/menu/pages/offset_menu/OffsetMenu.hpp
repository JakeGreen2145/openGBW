#pragma once

#include "../Menu.hpp"
#include <string>

// Menu for adjusting the grind weight offset
class OffsetMenu : public Menu<double> {
    private:
        // private constructor for singleton
        OffsetMenu();
        static OffsetMenu instance;

    public:

        // Accessor
        static OffsetMenu& getOffsetMenu();

        void displayMenu(U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2) override;

        void handleEncoderChange(int encoderDelta) override;

        void handleEncoderClick(AiEsp32RotaryEncoder encoder) override;
};
