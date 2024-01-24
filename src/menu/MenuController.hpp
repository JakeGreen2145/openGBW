#pragma once

#include "./pages/main_menu/MainMenu.hpp"
#include "./pages/closed_menu/ClosedMenu.hpp"
#include "./pages/offset_menu/OffsetMenu.hpp"
#include "./pages/calibration_menu/CalibrateMenu.hpp"
#include "./pages/cup_menu/CupMenu.hpp"
#include "./pages/grind_mode_menu/GrindModeMenu.hpp"
#include "./pages/reset_menu/ResetMenu.hpp"
#include "./pages/scale_mode_menu/ScaleModeMenu.hpp"
#include "./pages/sleep_menu/SleepMenu.hpp"

extern MainMenu& mainMenu; // Controls selected setting
extern ClosedMenu& closedMenu; // Controls setWeight
extern OffsetMenu& offsetMenu; // Controls grind weight offset
extern CalibrateMenu& calibrateMenu; // Controls load cell calibration
extern CupMenu& cupMenu; // Controls cup weight setting
extern GrindModeMenu& grindModeMenu; // Controls the grind mode
extern ResetMenu& resetMenu; // Handles resetting to default configuration
extern ScaleModeMenu& scaleModeMenu; // Handles whether the grinder should run or not
extern SleepMenu& sleepMenu; // Handles sleep timeout setting

// Create all singleton menuPages and begin loop to handle rotaryEncoder I/O
void setupMenu();
