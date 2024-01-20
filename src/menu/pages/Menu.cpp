#include "Menu.hpp"
#include <string>


// ------- Initialize static vars -------
template <typename T>
MenuId Menu<T>::activeMenu = NONE;

template <typename T>
GrinderState Menu<T>::grinderState = STATUS_EMPTY;

// template <typename T>
// int Menu<T>::encoderValue = 0;
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


// ------- Setters -------
template <typename T>
void Menu<T>::setValue(T newValue) {
    value = newValue;
}

template <typename T>
void Menu<T>::setActiveMenu(MenuId newActiveMenu) {
    activeMenu = newActiveMenu;
}

template <typename T>
void Menu<T>::setGrinderState(GrinderState newGrinderState) {
    grinderState = newGrinderState;
}


// ------- Getters ------- 
template <typename T>
T Menu<T>::getValue() const {
    return value;
}

template <typename T>
MenuId Menu<T>::getActiveMenu() {
    return activeMenu;
}

template <typename T>
GrinderState Menu<T>::getGrinderState() {
    return grinderState;
}

