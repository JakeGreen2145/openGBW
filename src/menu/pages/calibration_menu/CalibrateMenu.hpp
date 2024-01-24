#pragma once

#include "../Menu.hpp"
#include <string>
#include <SimpleKalmanFilter.h>
#include "HX711.h"

// Scale objects for measuring calibration weight
// TODO: move these to a scale class that can be read from.
extern HX711 loadcell;
extern SimpleKalmanFilter kalmanFilter;

// Menu for adjusting the grind weight offset
class CalibrateMenu : public Menu<double> {
    private:
        // private constructor for singleton
        CalibrateMenu();
        static CalibrateMenu instance;

    public:

        // Accessor
        static CalibrateMenu& getCalibrateMenu();

        void displayMenu(U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2) override;

        void handleEncoderChange(int encoderDelta) override;

        void handleEncoderClick(AiEsp32RotaryEncoder encoder) override;

        void setValue(double newValue);
};
