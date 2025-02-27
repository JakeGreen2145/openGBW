#include "display.hpp"


/* 
  U8G2_<controller>_<display>_<memory>_<communication> 
  memory
    "1"	one page
    "2"	two pages
    "f"	full frame buffer
  communication
    "SW SPI"

*/
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0);

TaskHandle_t DisplayTask;

void CenterPrintToScreen(char const *str, u8g2_uint_t y) {
  u8g2_uint_t width = u8g2.getStrWidth(str);
  u8g2.setCursor(128 / 2 - width / 2, y);
  u8g2.print(str);
}

void LeftPrintToScreen(char const *str, u8g2_uint_t y)
{
  u8g2_uint_t width = u8g2.getStrWidth(str);
  u8g2.setCursor(5, y);
  u8g2.print(str);
}

void LeftPrintActiveToScreen(char const *str, u8g2_uint_t y)
{
  u8g2_uint_t width = u8g2.getStrWidth(str);
  u8g2.setDrawColor(1);
  u8g2.drawBox(3, y - 1, 122, 14);
  u8g2.setDrawColor(0);
  u8g2.setCursor(5, y);
  u8g2.print(str);
  u8g2.setDrawColor(1);
}

void RightPrintToScreen(char const *str, u8g2_uint_t y)
{
  u8g2_uint_t width = u8g2.getStrWidth(str);
  u8g2.setCursor(123-width, y);
  u8g2.print(str);
}

void showMenu() {
    const char* prevName = mainMenu.getPrevMenuName();
    const char* selectedName = mainMenu.getSelectedMenuName();
    const char* nextName = mainMenu.getNextMenuName();
    char buf[3];
    u8g2.clearBuffer();
    u8g2.setFontPosTop();
    u8g2.setFont(u8g2_font_7x14B_tf);
    CenterPrintToScreen("Menu", 0);
    u8g2.setFont(u8g2_font_7x13_tr);
    LeftPrintToScreen(prevName, 19);
    LeftPrintActiveToScreen(selectedName, 35);
    LeftPrintToScreen(nextName, 51);

    u8g2.sendBuffer();
}

void showOffsetMenu(){
  char buf[16];
  u8g2.clearBuffer();
  u8g2.setFontPosTop();
  u8g2.setFont(u8g2_font_7x14B_tf);
  CenterPrintToScreen("Adjust offset", 0);
  u8g2.setFont(u8g2_font_7x13_tr);
  snprintf(buf, sizeof(buf), "%3.2fg", offsetMenu.getValue());
  CenterPrintToScreen(buf, 28);
  u8g2.sendBuffer();
}

void showSleepMenu() {
  char buf[16];
  u8g2.clearBuffer();
  u8g2.setFontPosTop();
  u8g2.setFont(u8g2_font_7x14B_tf);
  CenterPrintToScreen("Screen timeout", 0);
  u8g2.setFont(u8g2_font_7x13_tr);
  int timeoutSeconds = ((int)sleepMenu.getValue())/1000;
  snprintf(buf, sizeof(buf), "%d seconds", timeoutSeconds);
  CenterPrintToScreen(buf, 28);
  u8g2.sendBuffer();
}

void showScaleModeMenu()
{
  char buf[16];
  u8g2.clearBuffer();
  u8g2.setFontPosTop();
  u8g2.setFont(u8g2_font_7x14B_tf);
  CenterPrintToScreen("Set Scale Mode", 0);
  u8g2.setFont(u8g2_font_7x13_tr);
  if(scaleModeMenu.getValue()){
    LeftPrintToScreen("GBW", 19);
    LeftPrintActiveToScreen("Scale only", 35);
  }
  else{
    LeftPrintActiveToScreen("GBW", 19);
    LeftPrintToScreen("Scale only", 35);
  }
  u8g2.sendBuffer();
}

void showGrindModeMenu()
{
  char buf[16];
  u8g2.clearBuffer();
  u8g2.setFontPosTop();
  u8g2.setFont(u8g2_font_7x14B_tf);
  CenterPrintToScreen("Set Grinder ", 0);
  CenterPrintToScreen("Sart/Stop Mode", 19);
  u8g2.setFont(u8g2_font_7x13_tr);
  if (grindMode)
  {
    LeftPrintActiveToScreen("Continuous", 35);
    LeftPrintToScreen("Impulse", 51);
  }
  else
  {
    LeftPrintToScreen("Continuous", 35);
    LeftPrintActiveToScreen("Impulse", 51);
  }
  u8g2.sendBuffer();
}

void showCupMenu()
{
  char buf[16];
  u8g2.clearBuffer();
  u8g2.setFontPosTop();
  u8g2.setFont(u8g2_font_7x14B_tf);
  CenterPrintToScreen("Cup Weight", 0);
  u8g2.setFont(u8g2_font_7x13_tr);
  snprintf(buf, sizeof(buf), "%3.1fg", scaleWeight);
  CenterPrintToScreen(buf, 19);
  LeftPrintToScreen("Place cup on scale", 35);
  LeftPrintToScreen("and press button", 51);
  u8g2.sendBuffer();
}

void showCalibrationMenu(){
  u8g2.clearBuffer();
  u8g2.setFontPosTop();
  u8g2.setFont(u8g2_font_7x14B_tf);
  CenterPrintToScreen("Calibration", 0);
  u8g2.setFont(u8g2_font_7x13_tr);
  CenterPrintToScreen("Place 100g weight", 19);
  CenterPrintToScreen("on scale and", 35);
  CenterPrintToScreen("press button", 51);
  u8g2.sendBuffer();
}

void showResetMenu()
{
  bool greset = resetMenu.getValue();
  char buf[16];
  u8g2.clearBuffer();
  u8g2.setFontPosTop();
  u8g2.setFont(u8g2_font_7x14B_tf);
  CenterPrintToScreen("Reset to defaults?", 0);
  u8g2.setFont(u8g2_font_7x13_tr);
  if (greset)
  {
    LeftPrintActiveToScreen("Confirm", 19);
    LeftPrintToScreen("Cancel", 35);
  }
  else
  {
    LeftPrintToScreen("Confirm", 19);
    LeftPrintActiveToScreen("Cancel", 35);
  }
  u8g2.sendBuffer();
}

// Show the active setting submenu
void showSetting(){
  
  MenuId activeMenu = DeviceState::getActiveMenu();

  if(activeMenu == OFFSET) {
    showOffsetMenu();
  }
  else if(activeMenu == CUP_WEIGHT_MENU) {
    showCupMenu();
  }
  else if (activeMenu == CALIBRATE) {
    showCalibrationMenu();
  }
  else if (activeMenu == SCALE_MODE) {
    showScaleModeMenu();
  }
  else if (activeMenu == GRINDING_MODE) {
    showGrindModeMenu();
  }
  else if (activeMenu == RESET) {
    showResetMenu();
  }
  else if (activeMenu == SLEEP) {
    showSleepMenu();
  }
}

void updateDisplay( void * parameter) {
  char buf[64];
  char buf2[64];

  for(;;) {
    u8g2.clearBuffer();
    // Set screen to sleep if timeout is reached. Wake on scale change or encoder action.
    long sleepTimeout = sleepMenu.getValue();
    if ((millis() - lastSignificantWeightChangeAt > sleepTimeout) && (millis() - lastEncoderActionAt > sleepTimeout)) {
      u8g2.sendBuffer();
      delay(100);
      continue;
    }

    GrinderState grinderState = DeviceState::getGrinderState();

    if (scaleLastUpdatedAt == 0) {
      u8g2.setFontPosTop();
      u8g2.drawStr(0, 20, "Initializing...");
    } else if (!scaleReady) {
      u8g2.setFontPosTop();
      u8g2.drawStr(0, 20, "SCALE ERROR");
    } else {
      if (grinderState == STATUS_GRINDING_IN_PROGRESS) {
        u8g2.setFontPosTop();
        u8g2.setFont(u8g2_font_7x13_tr);
        CenterPrintToScreen("Grinding...", 0);


        u8g2.setFontPosCenter();
        u8g2.setFont(u8g2_font_7x14B_tf);
        u8g2.setCursor(3, 32);
        snprintf(buf, sizeof(buf), "%3.1fg", scaleWeight - cupWeightEmpty);
        u8g2.print(buf);

        u8g2.setFontPosCenter();
        u8g2.setFont(u8g2_font_unifont_t_symbols);
        u8g2.drawGlyph(64, 32, 0x2794);

        u8g2.setFontPosCenter();
        u8g2.setFont(u8g2_font_7x14B_tf);
        u8g2.setCursor(84, 32);
        snprintf(buf, sizeof(buf), "%3.1fg", setWeight);
        u8g2.print(buf);

        u8g2.setFontPosBottom();
        u8g2.setFont(u8g2_font_7x13_tr);
        snprintf(buf, sizeof(buf), "%3.1fs", startedGrindingAt > 0 ? (double)(millis() - startedGrindingAt) / 1000 : 0);
        CenterPrintToScreen(buf, 64);
      } else if (grinderState == STATUS_EMPTY) {
        u8g2.setFontPosTop();
        u8g2.setFont(u8g2_font_7x13_tr);
        CenterPrintToScreen("Weight:", 0);

        u8g2.setFont(u8g2_font_7x14B_tf);
        u8g2.setFontPosCenter();
        u8g2.setCursor(0, 28);
        snprintf(buf, sizeof(buf), "%3.1fg", abs(scaleWeight));
        CenterPrintToScreen(buf, 32);

        u8g2.setFont(u8g2_font_7x13_tf);
        u8g2.setFontPosCenter();
        u8g2.setCursor(5, 50);
        snprintf(
          buf2,
          sizeof(buf2),
          "Set: %3.1fg",
          closedMenu.getValue()
        );
        LeftPrintToScreen(buf2, 50);

        
      } else if (grinderState == STATUS_GRINDING_FAILED) {

        u8g2.setFontPosTop();
        u8g2.setFont(u8g2_font_7x14B_tf);
        CenterPrintToScreen("Grinding failed", 0);

        u8g2.setFontPosTop();
        u8g2.setFont(u8g2_font_7x13_tr);
        CenterPrintToScreen("Press the balance", 32);
        CenterPrintToScreen("to reset", 42);
      } else if (grinderState == STATUS_GRINDING_FINISHED) {

        u8g2.setFontPosTop();
        u8g2.setFont(u8g2_font_7x13_tr);
        u8g2.setCursor(0, 0);
        CenterPrintToScreen("Grinding finished", 0);

        u8g2.setFontPosCenter();
        u8g2.setFont(u8g2_font_7x14B_tf);
        u8g2.setCursor(3, 32);
        snprintf(buf, sizeof(buf), "%3.1fg", scaleWeight - cupWeightEmpty);
        u8g2.print(buf);

        u8g2.setFontPosCenter();
        u8g2.setFont(u8g2_font_unifont_t_symbols);
        u8g2.drawGlyph(64, 32, 0x2794);

        u8g2.setFontPosCenter();
        u8g2.setFont(u8g2_font_7x14B_tf);
        u8g2.setCursor(84, 32);
        snprintf(buf, sizeof(buf), "%3.1fg", setWeight);
        u8g2.print(buf);

        u8g2.setFontPosBottom();
        u8g2.setFont(u8g2_font_7x13_tr);
        u8g2.setCursor(64, 64);
        snprintf(buf, sizeof(buf), "%3.1fs", (double)(finishedGrindingAt - startedGrindingAt) / 1000);
        CenterPrintToScreen(buf, 64);
      }
      else if (grinderState == STATUS_IN_MENU)
      {
        showMenu();
      }
      else if (grinderState == STATUS_IN_SUBMENU)
      {
        showSetting();
      }
    }
    u8g2.sendBuffer();
    // delay(100);
  }
}

void setupDisplay() {
  u8g2.begin();
  u8g2.setFont(u8g2_font_7x13_tr);
  u8g2.setFontPosTop();
  u8g2.drawStr(0, 20, "Hello");

  xTaskCreatePinnedToCore(
      updateDisplay, /* Function to implement the task */
      "Display", /* Name of the task */
      10000,  /* Stack size in words */
      NULL,  /* Task input parameter */
      0,  /* Priority of the task */
      &DisplayTask,  /* Task handle. */
      1); /* Core where the task should run */
}
