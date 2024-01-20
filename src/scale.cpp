#include "scale.hpp"
#include <MathBuffer.h>
#include <Preferences.h>

HX711 loadcell;
SimpleKalmanFilter kalmanFilter(0.02, 0.02, 0.01);

Preferences preferences;

#define ABS(a) (((a) > 0) ? (a) : ((a) * -1))

TaskHandle_t ScaleTask;
TaskHandle_t ScaleStatusTask;

double scaleWeight = 0; //current weight
double setWeight = 0; //desired amount of coffee
double setCupWeight = 0; //cup weight set by user
double offset = 0; //stop x grams prios to set weight
bool scaleMode = false; //use as regular scale with timer if true
bool grindMode = false;  //false for impulse to start/stop grinding, true for continuous on while grinding
bool grinderActive = false; //needed for continuous mode
MathBuffer<double, 100> weightHistory;

// TODO: get these from menu classes
    // offset = preferences.getDouble("offset", (double)COFFEE_DOSE_OFFSET);
    // setCupWeight = preferences.getDouble("cup", (double)CUP_WEIGHT);
    // scaleMode = preferences.getBool("scaleMode", false);
    // grindMode = preferences.getBool("grindMode", false);

unsigned long scaleLastUpdatedAt = 0;
unsigned long lastSignificantWeightChangeAt = 0;
unsigned long lastTareAt = 0; // if 0, should tare load cell, else represent when it was last tared
bool scaleReady = false;
double cupWeightEmpty = 0; // measured actual cup weight
unsigned long startedGrindingAt = 0;
unsigned long finishedGrindingAt = 0;

bool newOffset = false;

void tareScale() {
  Serial.println("Taring scale");
  loadcell.tare(TARE_MEASURES);
  lastTareAt = millis();
}

void grinderToggle()
{
  if(!scaleMode){
    if(grindMode){
      grinderActive = !grinderActive;
      digitalWrite(GRINDER_ACTIVE_PIN, grinderActive);
    }
    else{
      digitalWrite(GRINDER_ACTIVE_PIN, 1);
      delay(100);
      digitalWrite(GRINDER_ACTIVE_PIN, 0);
    }
  }
}

void scaleStatusLoop(void *p) {
  double tenSecAvg;
  for (;;) {
    // recalibrate scale if new calibration has been set
    // TODO: control this from the calibrate menu
    bool isNewScaleCalibrationSet = false;
    if (isNewScaleCalibrationSet) {
        preferences.begin("scale", false);
        double newCalibrationValue = preferences.getDouble("calibration", (double)LOADCELL_SCALE_FACTOR);
        preferences.end();
        loadcell.set_scale(newCalibrationValue);
    }

    tenSecAvg = weightHistory.averageSince((int64_t)millis() - 10000);
    
    // TODO: add GrinderState for sleep
    if (ABS(tenSecAvg - scaleWeight) > SIGNIFICANT_WEIGHT_CHANGE) {
      lastSignificantWeightChangeAt = millis();
    }

    GrinderState grinderState = Menu<void*>::getGrinderState();
    if (grinderState == STATUS_EMPTY) {
      if (millis() - lastTareAt > TARE_MIN_INTERVAL && ABS(tenSecAvg) > 0.2 && tenSecAvg < 3 && scaleWeight < 3) {
        // tare if: not tared recently, more than 0.2 away from 0, less than 3 grams total (also works for negative weight)
        lastTareAt = 0;
      }

      // Start grinding if both min and max weight detected in the past 1s are less than cup weight + detection tolerance.
      if (ABS(weightHistory.minSince((int64_t)millis() - 1000) - setCupWeight) < CUP_DETECTION_TOLERANCE &&
          ABS(weightHistory.maxSince((int64_t)millis() - 1000) - setCupWeight) < CUP_DETECTION_TOLERANCE)
      {
        // using average over last 500ms as empty cup weight
        Serial.println("Starting grinding");
        cupWeightEmpty = weightHistory.averageSince((int64_t)millis() - 500);
        Menu<void*>::setGrinderState(STATUS_GRINDING_IN_PROGRESS);
        
        if(!scaleMode){
          newOffset = true;
          startedGrindingAt = millis();
        }
        
        grinderToggle();
        continue;
      }
    } else if (grinderState == STATUS_GRINDING_IN_PROGRESS) {
      if (!scaleReady) {
        
        grinderToggle();
        Menu<void*>::setGrinderState(STATUS_GRINDING_FAILED);
      }
      //Serial.printf("Scale mode: %d\n", scaleMode);
      //Serial.printf("Started grinding at: %d\n", startedGrindingAt);
      //Serial.printf("Weight: %f\n", cupWeightEmpty - scaleWeight);
      if (scaleMode && startedGrindingAt == 0 && scaleWeight - cupWeightEmpty >= 0.1)
      {
        Serial.printf("Started grinding at: %d\n", millis());
        startedGrindingAt = millis();
        continue;
      }

      if (millis() - startedGrindingAt > MAX_GRINDING_TIME && !scaleMode) {
        Serial.println("Failed because grinding took too long");
        
        grinderToggle();
        Menu<void*>::setGrinderState(STATUS_GRINDING_FAILED);
        continue;
      }

      if (
          millis() - startedGrindingAt > 2000 &&                                  // started grinding at least 2s ago
          scaleWeight - weightHistory.firstValueOlderThan(millis() - 2000) < 1 && // less than a gram has been grinded in the last 2 second
          !scaleMode)
      {
        Serial.println("Failed because no change in weight was detected");
        
        grinderToggle();
        Menu<void*>::setGrinderState(STATUS_GRINDING_FAILED);
        continue;
      }

      if (weightHistory.minSince((int64_t)millis() - 200) < cupWeightEmpty - CUP_DETECTION_TOLERANCE && !scaleMode) {
        Serial.printf("Failed because weight too low, min: %f, min value: %f\n", weightHistory.minSince((int64_t)millis() - 200), CUP_WEIGHT + CUP_DETECTION_TOLERANCE);
        
        grinderToggle();
        Menu<void*>::setGrinderState(STATUS_GRINDING_FAILED);
        continue;
      }
      double currentOffset = offset;
      if(scaleMode){
        currentOffset = 0;
      }
      if (weightHistory.maxSince((int64_t)millis() - 200) >= cupWeightEmpty + setWeight + currentOffset) {
        Serial.println("Finished grinding");
        finishedGrindingAt = millis();
        
        grinderToggle();
        Menu<void*>::setGrinderState(STATUS_GRINDING_FINISHED);
        continue;
      }
    } else if (grinderState == STATUS_GRINDING_FINISHED) {
      double currentWeight = weightHistory.averageSince((int64_t)millis() - 500);
      if (scaleWeight < 5) {
        Serial.println("Going back to empty");
        startedGrindingAt = 0;
        Menu<void*>::setGrinderState(STATUS_EMPTY);
        continue;
      }
      else if (currentWeight != setWeight + cupWeightEmpty && millis() - finishedGrindingAt > 1500 && newOffset)
      {
        offset += setWeight + cupWeightEmpty - currentWeight;
        if(ABS(offset) >= setWeight){
          offset = COFFEE_DOSE_OFFSET;
        }
        preferences.begin("scale", false);
        preferences.putDouble("offset", offset);
        preferences.end();
        newOffset = false;
      }
    } else if (grinderState == STATUS_GRINDING_FAILED) {
      if (scaleWeight >= GRINDING_FAILED_WEIGHT_TO_RESET) {
        Serial.println("Going back to empty");
        Menu<void*>::setGrinderState(STATUS_EMPTY);
        continue;
      }
    }
    delay(50);
  }
}

void updateScale( void * parameter) {
  float lastEstimate;


  for (;;) {
    if (lastTareAt == 0) {
      Serial.println("retaring scale");
      Serial.println("current offset");
      Serial.println(offset);
      tareScale();
    }
    if (loadcell.wait_ready_timeout(300)) {
      lastEstimate = kalmanFilter.updateEstimate(loadcell.get_units(5));
      scaleWeight = lastEstimate;
      scaleLastUpdatedAt = millis();
      weightHistory.push(scaleWeight);
      scaleReady = true;
    } else {
      Serial.println("HX711 not found.");
      scaleReady = false;
    }
  }
}


void setupScale() {
  // rotaryEncoder.begin();
  // rotaryEncoder.setup(readEncoderISR);
  // // set boundaries and if values should cycle or not
  // // in this example we will set possible values between 0 and 1000;
  // bool circleValues = true;
  // rotaryEncoder.setBoundaries(-10000, 10000, circleValues); // minValue, maxValue, circleValues true|false (when max go to min and vice versa)

  // /*Rotary acceleration introduced 25.2.2021.
  //  * in case range to select is huge, for example - select a value between 0 and 1000 and we want 785
  //  * without accelerateion you need long time to get to that number
  //  * Using acceleration, faster you turn, faster will the value raise.
  //  * For fine tuning slow down.
  //  */
  // // rotaryEncoder.disableAcceleration(); //acceleration is now enabled by default - disable if you dont need it
  // rotaryEncoder.setAcceleration(100); // or set the value - larger number = more accelearation; 0 or 1 means disabled acceleration


  loadcell.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);

  pinMode(GRINDER_ACTIVE_PIN, OUTPUT);
  digitalWrite(GRINDER_ACTIVE_PIN, 0);

  preferences.begin("scale", false);
  
  double scaleFactor = preferences.getDouble("calibration", (double)LOADCELL_SCALE_FACTOR);
  setWeight = preferences.getDouble("setWeight", (double)COFFEE_DOSE_WEIGHT);
  offset = preferences.getDouble("offset", (double)COFFEE_DOSE_OFFSET);
  setCupWeight = preferences.getDouble("cup", (double)CUP_WEIGHT);
  scaleMode = preferences.getBool("scaleMode", false);
  grindMode = preferences.getBool("grindMode", false);

  preferences.end();
  
  loadcell.set_scale(scaleFactor);

  xTaskCreatePinnedToCore(
      updateScale, /* Function to implement the task */
      "Scale",     /* Name of the task */
      10000,       /* Stack size in words */
      NULL,        /* Task input parameter */
      0,           /* Priority of the task */
      &ScaleTask,  /* Task handle. */
      1);          /* Core where the task should run */

  xTaskCreatePinnedToCore(
      scaleStatusLoop, /* Function to implement the task */
      "ScaleStatus", /* Name of the task */
      10000,  /* Stack size in words */
      NULL,  /* Task input parameter */
      0,  /* Priority of the task */
      &ScaleStatusTask,  /* Task handle. */
      1  /* Core where the task should run */
    );
}
