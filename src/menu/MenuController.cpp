#include "MenuController.hpp"

TaskHandle_t MenuTask;
static AiEsp32RotaryEncoder rotaryEncoder = AiEsp32RotaryEncoder(ROTARY_ENCODER_A_PIN, ROTARY_ENCODER_B_PIN, ROTARY_ENCODER_BUTTON_PIN, ROTARY_ENCODER_VCC_PIN, ROTARY_ENCODER_STEPS);
MainMenu& mainMenu = MainMenu::getMainMenu(); // controls selected setting
ClosedMenu& closedMenu = ClosedMenu::getClosedMenu(); // controls setWeight
static Preferences controllerPreferences;
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
    return encoderValue;
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
    // else if(grinderState == STATUS_IN_SUBMENU){
    //     MenuId currentSetting = mainMenu.getValue();
    //     if(currentSetting == 2) {
    //         controllerPreferences.begin("scale", false);
    //         controllerPreferences.putDouble("offset", offset);
    //         controllerPreferences.end();
    //         grinderState = STATUS_IN_MENU;
    //         currentSetting = -1;
    //     }
    //     else if (currentSetting == 0)
    //     {
    //         if(scaleWeight > 30) {       //prevent accidental setting with no cup
    //         setCupWeight = scaleWeight;
    //         Serial.println(setCupWeight);
            
    //         controllerPreferences.begin("scale", false);
    //         controllerPreferences.putDouble("cup", setCupWeight);
    //         controllerPreferences.end();
    //         grinderState = STATUS_IN_MENU;
    //         currentSetting = -1;
    //         }
    //     }
    //     else if (currentSetting == 1)
    //     {
    //         controllerPreferences.begin("scale", false);
    //         double newCalibrationValue = controllerPreferences.getDouble("calibration", (double)newCalibrationValue) * (scaleWeight / 100);
    //         Serial.print("New scale factor set to: ");
    //         Serial.println(newCalibrationValue);
    //         controllerPreferences.putDouble("calibration", newCalibrationValue);
    //         controllerPreferences.end();
    //         isNewScaleCalibrationSet = true;
    //         grinderState = STATUS_IN_MENU;
    //         currentSetting = -1;
    //     }
    //     else if (currentSetting == 3)
    //     {
    //         controllerPreferences.begin("scale", false);
    //         controllerPreferences.putBool("scaleMode", scaleMode);
    //         controllerPreferences.end();
    //         grinderState = STATUS_IN_MENU;
    //         currentSetting = -1;
    //     }
    //     else if (currentSetting == 4)
    //     {
    //         controllerPreferences.begin("scale", false);
    //         controllerPreferences.putBool("grindMode", grindMode);
    //         controllerPreferences.end();
    //         grinderState = STATUS_IN_MENU;
    //         currentSetting = -1;
    //     }
    //     else if (currentSetting == 6)
    //     {
    //         if(greset){
    //             controllerPreferences.begin("scale", false);
    //             controllerPreferences.putDouble("calibration", (double)LOADCELL_SCALE_FACTOR);
    //             setWeight = (double)COFFEE_DOSE_WEIGHT;
    //             controllerPreferences.putDouble("setWeight", (double)COFFEE_DOSE_WEIGHT);
    //             offset = (double)COFFEE_DOSE_OFFSET;
    //             controllerPreferences.putDouble("offset", (double)COFFEE_DOSE_OFFSET);
    //             setCupWeight = (double)CUP_WEIGHT;
    //             controllerPreferences.putDouble("cup", (double)CUP_WEIGHT);
    //             scaleMode = false;
    //             controllerPreferences.putBool("scaleMode", false);
    //             grindMode = false;
    //             controllerPreferences.putBool("grindMode", false);
    //             isNewScaleCalibrationSet = true;
    //             controllerPreferences.end();
    //         }
    //         grinderState = STATUS_IN_MENU;
    //         currentSetting = -1;
    //     }
    // }
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
        // TODO: move this to classes
        // if(currentSetting == 2) { //offset menu
        //     Serial.print("Value: ");
        //     offset += ((float)encoderDelta) / 100;
        //     if(abs(offset) >= setWeight) {
        //         offset = setWeight;     //prevent nonsensical offsets
        //     }
        // }
        // // Toggleable Settings
        // else if(currentSetting == 3) {
        //     scaleMode = !scaleMode;
        // }
        // else if (currentSetting == 4) {
        //     grindMode = !grindMode;
        // }
        // else if (currentSetting == 6) {
        //     greset = !greset;
        // }
    }
}


void rotary_loop(void *p) {
    for(;;) {
        grinderState = Menu<void*>::getGrinderState();
        if (rotaryEncoder.encoderChanged()) {
            rotary_onChange();
        }
        if (rotaryEncoder.isEncoderButtonClicked()) {
            rotary_onButtonClick();
        }
    }
}


void setupMenu() {
    // 1) get all singleton menu classes
    // mainMenu = MainMenu::getMainMenu();
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
    // rotaryEncoder.disableAcceleration(); //acceleration is now enabled by default - disable if you dont need it
    rotaryEncoder.setAcceleration(100); // or set the value - larger number = more accelearation; 0 or 1 means disabled acceleration

    // 3) setup controllerPreferences
    controllerPreferences.begin("scale", false);
  
    // TODO: initialize menu objects with these values
    double scaleFactor = controllerPreferences.getDouble("calibration", (double)LOADCELL_SCALE_FACTOR);
    double setWeight = controllerPreferences.getDouble("setWeight", (double)COFFEE_DOSE_WEIGHT);
    closedMenu.setValue(setWeight);
    // offset = controllerPreferences.getDouble("offset", (double)COFFEE_DOSE_OFFSET);
    // setCupWeight = controllerPreferences.getDouble("cup", (double)CUP_WEIGHT);
    // scaleMode = controllerPreferences.getBool("scaleMode", false);
    // grindMode = controllerPreferences.getBool("grindMode", false);

    controllerPreferences.end();


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