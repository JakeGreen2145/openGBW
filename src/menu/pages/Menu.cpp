#include "Menu.hpp"
#include <string>

// Initially menu will be closed
template <typename T>
MenuId Menu<T>::activeMenu = NONE;

template <typename T>
AiEsp32RotaryEncoder Menu<T>::rotaryEncoder = AiEsp32RotaryEncoder(ROTARY_ENCODER_A_PIN, ROTARY_ENCODER_B_PIN, ROTARY_ENCODER_BUTTON_PIN, ROTARY_ENCODER_VCC_PIN, ROTARY_ENCODER_STEPS);

template <typename T>
int Menu<T>::encoderValue = 0;
// Initially null
// template <typename T>
// Menu<T>& Menu<T>::instance = Menu();

// Constructor
// template <typename T>
// Menu<T>::Menu(T initialValue, std::string name, MenuId menuId)
//     : value(initialValue), name(name), menuId(menuId) {}

// Enter control loop
// template <typename T>
// Menu<T>& Menu<T>::getMenu(T initialValue, std::string name, MenuId menuId) {
//     if (instance == null){
//         instance = 
//     }
//     return instance;
// }

// setters
template <typename T>
void Menu<T>::setValue(T newValue) {
    value = newValue;
}

template <typename T>
void Menu<T>::setActiveMenu(MenuId activeMenu) {
    this->activeMenu = activeMenu;
}

// Getter method to retrieve the current value
template <typename T>
T Menu<T>::getValue() const {
    return value;
}

template <typename T>
MenuId Menu<T>::getActiveMenu() {
    return activeMenu;
}

