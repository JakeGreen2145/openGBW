#pragma once

#include "../Menu.hpp"
#include <string>

// Menu for selecting submenus. The value stored is a MenuId of the currently highlighted menu.
class ClosedMenu : public Menu<double> {
    private:
        // private constructor for singleton
        ClosedMenu();
        static ClosedMenu instance;

    public:

        // Accessor
        static ClosedMenu& getClosedMenu();

        void displayMenu(U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2) override;

        void handleEncoderChange(int encoderDelta) override;

        void handleEncoderClick(AiEsp32RotaryEncoder encoder) override;

        void setValue(double newValue);
};
