#pragma once

#include <string>
#include <AiEsp32RotaryEncoder.h>

#define CUP_WEIGHT 70
#define CUP_DETECTION_TOLERANCE 5 // 5 grams tolerance above or bellow cup weight to detect it

#define LOADCELL_DOUT_PIN 19
#define LOADCELL_SCK_PIN 18

#define LOADCELL_SCALE_FACTOR 7351

#define TARE_MEASURES 20 // use the average of measure for taring
#define SIGNIFICANT_WEIGHT_CHANGE 5 // 5 grams changes are used to detect a significant change
#define COFFEE_DOSE_WEIGHT 18
#define COFFEE_DOSE_OFFSET -2.5
#define MAX_GRINDING_TIME 20000 // 20 seconds diff
#define GRINDING_FAILED_WEIGHT_TO_RESET 150 // force on balance need to be measured to reset grinding

#define GRINDER_ACTIVE_PIN 33

#define TARE_MIN_INTERVAL 10 * 1000 // auto-tare at most once every 10 seconds

#define ROTARY_ENCODER_A_PIN 32
#define ROTARY_ENCODER_B_PIN 23
#define ROTARY_ENCODER_BUTTON_PIN 34
#define ROTARY_ENCODER_VCC_PIN -1
#define ROTARY_ENCODER_STEPS 4

enum GrinderState {
    STATUS_EMPTY = 0,
    STATUS_GRINDING_IN_PROGRESS = 1,
    STATUS_GRINDING_FINISHED = 2,
    STATUS_GRINDING_FAILED = 3,
    STATUS_IN_MENU = 4,
    STATUS_IN_SUBMENU = 5
};

extern double scaleWeight;
extern unsigned long scaleLastUpdatedAt;
extern unsigned long lastSignificantWeightChangeAt;
extern unsigned long lastEncoderActionAt;
extern unsigned long lastTareAt;
extern bool scaleReady;
extern GrinderState grinderState;
extern double cupWeightEmpty;
extern unsigned long startedGrindingAt;
extern unsigned long finishedGrindingAt;
extern double setWeight;
extern double offset;
extern bool scaleMode;
extern bool grindMode;
extern bool greset;
extern int menuItemsCount;
extern int currentMenuItem;
extern int currentSetting;

// Enum for menu IDs
enum MenuId {
    NONE = 0,
    MAIN_MENU = 1,
    CUP_WEIGHT_MENU = 2,
    CALIBRATE = 3,
    OFFSET = 4,
    SCALE_MODE = 5,
    GRINDING_MODE = 6,
    SLEEP = 7,
    EXIT = 8,
    RESET = 9
};

template <typename T>
class Menu {
private:
    // Constructor is private. setupMenu should be used to initialize menus
    // Menu(T initialValue, std::string name, MenuId menuId);
    // static Menu<T> instance;
protected:
    T value;
    std::string name;
    MenuId menuId;
    static int encoderValue;
    static MenuId activeMenu;
    static AiEsp32RotaryEncoder rotaryEncoder;
public:
    // Create singleton instance
    //static Menu<T>& getMenu(T initialValue, std::string name, MenuId menuId);

    // Display the menu options
    virtual void displayMenu();
    // Change the value
    virtual void incrementValue(T increment);

    // Interaction
    virtual void handleEncoderChange(int encoderValue, int encoderDirection);
    virtual void handleEncoderClick();

    // setters
    void setValue(T newValue);
    void setActiveMenu(MenuId activeMenu);

    // Getters
    T getValue() const;
    static MenuId getActiveMenu();

    // Virtual destructor (important for polymorphic behavior)
    virtual ~Menu() {}
};
