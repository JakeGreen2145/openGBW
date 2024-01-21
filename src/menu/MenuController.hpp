#pragma once

#include "./pages/main_menu/MainMenu.hpp"
#include "./pages/closed_menu/ClosedMenu.hpp"
#include "./pages/offset_menu/OffsetMenu.hpp"

extern MainMenu& mainMenu; // controls selected setting
extern ClosedMenu& closedMenu; // controls setWeight
extern OffsetMenu& offsetMenu; // controls grind weight offset

// Create all singleton menuPages and begin loop to handle rotaryEncoder I/O
void setupMenu();
