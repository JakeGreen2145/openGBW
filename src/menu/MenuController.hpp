#pragma once

#include "./pages/main_menu/MainMenu.hpp"
#include "./pages/closed_menu/ClosedMenu.hpp"
#include "./pages/offset_menu/OffsetMenu.hpp"
#include "./pages/calibration_menu/CalibrateMenu.hpp"

extern MainMenu& mainMenu; // controls selected setting
extern ClosedMenu& closedMenu; // controls setWeight
extern OffsetMenu& offsetMenu; // controls grind weight offset
extern CalibrateMenu& calibrateMenu;

// Create all singleton menuPages and begin loop to handle rotaryEncoder I/O
void setupMenu();
