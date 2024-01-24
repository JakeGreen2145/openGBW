#pragma once

#include "../Menu.hpp"


// Menu for adjusting the sleep timeout
class SleepMenu : public Menu<double> {
    private:
        // private constructor for singleton
        SleepMenu();
        static SleepMenu instance;

    public:

        // Accessor
        static SleepMenu& getSleepMenu();

        void displayMenu(U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2) override;

        void handleEncoderChange(int encoderDelta) override;

        void handleEncoderClick(AiEsp32RotaryEncoder encoder) override;

        void setValue(double newValue);
};
