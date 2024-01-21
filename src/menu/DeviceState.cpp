#include "DeviceState.hpp"


MenuId DeviceState::activeMenu = NONE;
GrinderState DeviceState::grinderState = STATUS_EMPTY;

// Setters
void DeviceState::setActiveMenu(MenuId newActiveMenu) {
    activeMenu = newActiveMenu;
}

void DeviceState::setGrinderState(GrinderState newGrinderState) {
    grinderState = newGrinderState;
}


// Getters
MenuId DeviceState::getActiveMenu() {
    return activeMenu;
}

GrinderState DeviceState::getGrinderState() {
    return grinderState;
}