#pragma once

#include "Menu.hpp"
#include <string>

// TODO: Make all menus singletons
class MainMenu : public Menu<MenuId> {
    private:
    // private constructor for singleton
    MainMenu(MenuId initialValue, std::string name, MenuId menuId);
    static MainMenu instance;

    public:

    // Accessor
    static MainMenu& getMainMenu(MenuId initialValue, std::string name, MenuId menuId);

    void displayMenu() override;

    void incrementValue(MenuId increment) override;

    void handleEncoderChange(int encoderValue, int encoderDirection) override;

    void handleEncoderClick() override;
};
