#pragma once

#include <SimpleKalmanFilter.h>
#include "HX711.h"
#include "./menu/MenuController.hpp"
#include "./menu/pages/closed_menu/ClosedMenu.hpp"
#include "./menu/pages/main_menu/MainMenu.hpp"
#include "./menu/pages/Menu.hpp"

class MenuItem
{
    public:
        int id;
        bool selected;
        char menuName[16];
        double increment;
        double *value;
};

extern double scaleWeight;
extern unsigned long scaleLastUpdatedAt;
extern unsigned long lastSignificantWeightChangeAt;
extern unsigned long lastTareAt;
extern bool scaleReady;
extern double cupWeightEmpty;
extern unsigned long startedGrindingAt;
extern unsigned long finishedGrindingAt;
extern double setWeight;
extern double offset;
extern bool scaleMode;
extern bool grindMode;

void setupScale();
