#include "MenuController.hpp"

TaskHandle_t MenuTask;
static AiEsp32RotaryEncoder rotaryEncoder = AiEsp32RotaryEncoder(ROTARY_ENCODER_A_PIN, ROTARY_ENCODER_B_PIN, ROTARY_ENCODER_BUTTON_PIN, ROTARY_ENCODER_VCC_PIN, ROTARY_ENCODER_STEPS);
static Preferences controllerPreferences;
MainMenu& mainMenu = MainMenu::getMainMenu(); // Controls selected setting
ClosedMenu& closedMenu = ClosedMenu::getClosedMenu(); // Controls setWeight
OffsetMenu& offsetMenu = OffsetMenu::getOffsetMenu(); // Controls grind weight offset
CalibrateMenu& calibrateMenu = CalibrateMenu::getCalibrateMenu(); // Controls load cell calibration
CupMenu& cupMenu = CupMenu::getCupMenu(); // Controls cup weight setting
GrindModeMenu& grindModeMenu = GrindModeMenu::getGrindModeMenu(); // Controls grind mode
ResetMenu& resetMenu = ResetMenu::getResetMenu(); // Resets to default settings
//double setCupWeight;
GrinderState grinderState = STATUS_EMPTY;
unsigned long lastEncoderActionAt = 0;

int encoderValue = 0;
// Change this to -1 to reverse encoder direction
int encoderDir = 1;

void readEncoderISR() {
    rotaryEncoder.readEncoder_ISR();
}

int getEncoderDelta() {
    int newValue = rotaryEncoder.readEncoder();
    int delta = (newValue - encoderValue) * -encoderDir;
    encoderValue = newValue;
    return delta;
}


void rotary_onButtonClick() {
    static unsigned long lastTimePressed = 0;
    // ignore multiple press in that time milliseconds
    if (millis() - lastTimePressed < 500) {
        return;
    }
    lastEncoderActionAt = millis();

    // Enter menu if currently on homepage
    if(grinderState == STATUS_EMPTY) {
        closedMenu.handleEncoderClick(rotaryEncoder);
    }
    // Select currentMenuItem if in main menu
    else if(grinderState == STATUS_IN_MENU) {
        mainMenu.handleEncoderClick(rotaryEncoder);
    }
    // TODO: move this logic to menu classes
    // handle clicks based on current menu if in submenu
    else if(grinderState == STATUS_IN_SUBMENU){
        MenuId activeSubmenu = DeviceState::getActiveMenu();
        if(activeSubmenu == OFFSET) {
            offsetMenu.handleEncoderClick(rotaryEncoder);
        }
        else if (activeSubmenu == CUP_WEIGHT_MENU)
        {
            cupMenu.handleEncoderClick(rotaryEncoder);
        }
        else if (activeSubmenu == CALIBRATE)
        {
            calibrateMenu.handleEncoderClick(rotaryEncoder);
        }
        // else if (currentSetting == 3)
        // {
        //     controllerPreferences.begin("scale", false);
        //     controllerPreferences.putBool("scaleMode", scaleMode);
        //     controllerPreferences.end();
        //     grinderState = STATUS_IN_MENU;
        //     currentSetting = -1;
        // }
        else if (activeSubmenu == GRINDING_MODE)
        {
            grindModeMenu.handleEncoderClick(rotaryEncoder);
        }
        else if (activeSubmenu == RESET)
        {
            // handle this here since resetMenu doesn't have access to all other menus
            if (resetMenu.getValue()) {
                closedMenu.setValue((double)COFFEE_DOSE_WEIGHT);
                offsetMenu.setValue((double)COFFEE_DOSE_OFFSET);
                cupMenu.setValue((double)CUP_WEIGHT);
                //scaleModeMenu.setValue(false);
                grindModeMenu.setValue(false);
                calibrateMenu.setValue((double)LOADCELL_SCALE_FACTOR);
            }
            resetMenu.setValue(false);
            DeviceState::setGrinderState(STATUS_IN_MENU);
            DeviceState::setActiveMenu(MAIN_MENU);
        }
    }
}

void rotary_onChange() {
    lastEncoderActionAt = millis();
    int encoderDelta = getEncoderDelta();
    // handle encoder change from outside menu
    if(grinderState == STATUS_EMPTY) {
        closedMenu.handleEncoderChange(encoderDelta);
    }
    // handle encoder change in main menu
    else if(grinderState == STATUS_IN_MENU) {
        mainMenu.handleEncoderChange(encoderDelta);
    }
    // handle encoder change in submenus
    else if(grinderState == STATUS_IN_SUBMENU) {
        MenuId activeSubmenu = DeviceState::getActiveMenu();
        // TODO: move this to classes
        if(activeSubmenu == OFFSET) { //offset menu
            offsetMenu.handleEncoderChange(encoderDelta);
        }
        // Toggleable Settings
        // else if(currentSetting == 3) {
        //     scaleMode = !scaleMode;
        // }
        else if (activeSubmenu == GRINDING_MODE) {
            grindModeMenu.handleEncoderChange(encoderDelta);
        }
        else if (activeSubmenu == RESET) {
            resetMenu.handleEncoderChange(encoderDelta);
        }
    }
}


void rotary_loop(void *p) {
    for(;;) {
        grinderState = DeviceState::getGrinderState();
        if (rotaryEncoder.encoderChanged()) {
            rotary_onChange();
        }
        if (rotaryEncoder.isEncoderButtonClicked()) {
            rotary_onButtonClick();
        }
    }
}


void setupMenu() {
    // 2) setup I/O
    rotaryEncoder.begin();
    rotaryEncoder.setup(readEncoderISR);
    // set boundaries and if values should cycle or not
    // in this example we will set possible values between 0 and 1000;
    bool circleValues = true;
    rotaryEncoder.setBoundaries(-10000, 10000, circleValues); // minValue, maxValue, circleValues true|false (when max go to min and vice versa)

    /*Rotary acceleration introduced 25.2.2021.
    * in case range to select is huge, for example - select a value between 0 and 1000 and we want 785
    * without accelerateion you need long time to get to that number
    * Using acceleration, faster you turn, faster will the value raise.
    * For fine tuning slow down.
    */
    rotaryEncoder.setAcceleration(100); // or set the value - larger number = more accelearation; 0 or 1 means disabled acceleration

    // 4) start loop to catch I/O
    xTaskCreatePinnedToCore(
        rotary_loop, /* Function to implement the task */
        "Menu Loop", /* Name of the task */
        10000,  /* Stack size in words */
        NULL,  /* Task input parameter */
        0,  /* Priority of the task */
        &MenuTask,  /* Task handle. */
        1  /* Core where the task should run */
    );
}