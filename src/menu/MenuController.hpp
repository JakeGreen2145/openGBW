#pragma once

#include "./pages/main_menu/MainMenu.hpp"
#include "./pages/closed_menu/ClosedMenu.hpp"

extern MainMenu& mainMenu; // controls selected setting
extern ClosedMenu& closedMenu; // controls setWeight

// Create all singleton menuPages and begin loop to handle rotaryEncoder I/O
void setupMenu();
