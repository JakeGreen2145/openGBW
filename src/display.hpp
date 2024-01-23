#pragma once

#include "scale.hpp"
#include <SPI.h>
#include <U8g2lib.h>
#include "./menu/MenuController.hpp"
#include "./menu/pages/closed_menu/ClosedMenu.hpp"
#include "./menu/pages/main_menu/MainMenu.hpp"
#include "./menu/pages/Menu.hpp"

extern unsigned long lastEncoderActionAt;

void setupDisplay();
