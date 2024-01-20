#pragma once

#include "../Menu.hpp"
#include <string>

// Menu for selecting submenus. The value stored is a MenuId of the currently highlighted menu.
class MainMenu : public Menu<MenuId> {
    private:
        // private constructor for singleton
        MainMenu();
        static MainMenu instance;

        int menuIndex = 0;

    public:

        // Getters
        static MainMenu& getMainMenu();
        const char* getSelectedMenuName();
        const char* getNextMenuName();
        const char* getPrevMenuName();

        void displayMenu(U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2) override;

        void incrementValue(MenuId increment) override;

        void handleEncoderChange(int encoderDelta) override;

        void handleEncoderClick(AiEsp32RotaryEncoder encoder) override;
};
