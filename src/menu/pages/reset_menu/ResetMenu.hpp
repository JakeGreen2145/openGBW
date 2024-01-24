#pragma once

#include "../Menu.hpp"
#include <string>

// Menu for resetting to default settings
class ResetMenu : public Menu<bool> {
    private:
        // private constructor for singleton
        ResetMenu();
        static ResetMenu instance;

    public:

        // Accessor
        static ResetMenu& getResetMenu();

        void displayMenu(U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2) override;

        void handleEncoderChange(int encoderDelta) override;

        void handleEncoderClick(AiEsp32RotaryEncoder encoder) override;
};
