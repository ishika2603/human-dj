/*
* touch sensing module to calibrate voltage thresholds and update touch states whenever a touch is detected. 
* Used within FSM model in humandj.ino to update/initialize variables.
*/


#ifndef TESTING

int helperAnalogRead(int pin){
  /*
  * Function wrapper for analogRead, custom definition used for testing.
  */
  return analogRead(pin)
}

void calibrate_voltage() {
    /*
    Calculates an average baseline voltage threshold for each human participant. 
    Uses a moving average value, for better sensitivity a variance method also included.

    returns: void
    */
    for (int i = 0; i < NUM_PEOPLE; i++) {
      int CALIBRATION_TIMES = 500;
      int totalValue = 0;
      // int totalSquaredValue = 0;
      for (int j = 0; j < CALIBRATION_TIMES; j++) {
        int cur_val = helperAnalogRead(touchPins[i]);
        totalValue += cur_val;
        // totalSquaredValue += cur_val * cur_val;
      }

      int initialValue = totalValue / CALIBRATION_TIMES;
      touchThresholds[i] = initialValue - 120; // Set threshold slightly below initial value

      // alternate method is to calculate based on variance/mean etc
      // Compute mean and standard deviation
      // float mean = (float)totalValue / CALIBRATION_TIMES;
      // float variance = ((float)totalSquaredValue / CALIBRATION_TIMES) - (mean * mean);
      // float stddev = sqrt(variance);

      // // Set the threshold slightly below the mean to detect significant dips
      // touchThresholds[i] = mean - (3 * stddev); // Adjust the multiplier as per sensitivity needs
      #ifdef DEBUG
      Serial.print("Calibrated threshold for Person ");
      Serial.print(i + 1);
      Serial.print(": ");
      Serial.println(touchThresholds[i]);
      #endif

    }
    #ifdef DEBUG
    Serial.println();
    #endif
}

void update_touch_states(int* touch_states) {
    /*
    Updates the touch states based on who the DJ is currently touching / or not touching.
    returns: void
    */
    int sensorValue;
    for (int i = 0; i < NUM_PEOPLE; i++) {
        // read 10 times for some person
        int CALIBRATION_TIMES = 500;
        int totalTouchValue = 0;
        for (int j = 0; j < CALIBRATION_TIMES; j++) {
          sensorValue = helperAnalogRead(touchPins[i]);
          totalTouchValue += sensorValue;
        }

        int touchValue = totalTouchValue / CALIBRATION_TIMES;

        // Open Serial Plotter to view these values real-time, useful for debugging
        #ifdef DEBUG
        Serial.print("PersonAvg");
        Serial.print(i);
        Serial.print(":"); 
        Serial.print(touchValue); 
        Serial.print("\t");

        Serial.print("threshold");
        Serial.print(i);
        Serial.print(":"); 
        Serial.print(touchThresholds[i]); 
        Serial.print("\t");
        #endif

        if (touchValue < touchThresholds[i]) {
            touch_states[i] = 1; // Update the state in the passed-in array
        } else {
            touch_states[i] = 0; // Update the state in the passed-in array
        }
    }
    #ifdef DEBUG
    Serial.println();
    #endif
}

/* TESTING MODULE */
#else

/* global vars for mock functions */
// const int NUM_PEOPLE = 4; // Test with 2 participants for simplicity
int mockReadings[NUM_PEOPLE][10] = {
        {500, 510, 520, 530, 540, 550, 560, 570, 580, 590}, // Person 1 readings
        {600, 610, 620, 630, 640, 650, 660, 670, 680, 690}  // Person 2 readings
    };
int readIndex[NUM_PEOPLE] = {0, 0, 0, 0};

/* mock functions */
int helperAnalogRead(int pin){
  if (pin == 0) return mockReadings[0][readIndex[0]++];
  if (pin == 1) return mockReadings[1][readIndex[1]++];
  if (pin == 2) return 0;
  if (pin == 3) return 1000;
  if (pin == 4) return 381;
  if (pin == 5) return 490;
  if (pin == 6) return 300;
  if (pin == 7) return 679;

}

void calibrate_voltage() {
    for (int i = 0; i < NUM_PEOPLE; i++) {
      int CALIBRATION_TIMES = 10;
      int totalValue = 0;
      for (int j = 0; j < CALIBRATION_TIMES; j++) {
        int cur_val = helperAnalogRead(touchPins[i]);
        totalValue += cur_val;
      }

      int initialValue = totalValue / CALIBRATION_TIMES;
      touchThresholds[i] = initialValue - 120; // Set threshold slightly below initial value
    }
}


void update_touch_states(int* touch_states) {
    int sensorValue;
    for (int i = 0; i < NUM_PEOPLE; i++) {
        // read 10 times for some person
        int CALIBRATION_TIMES = 10;
        int totalTouchValue = 0;
        for (int j = 0; j < CALIBRATION_TIMES; j++) {
          sensorValue = helperAnalogRead(touchPins[i]);
          totalTouchValue += sensorValue;
        }

        int touchValue = totalTouchValue / CALIBRATION_TIMES;

        if (touchValue < touchThresholds[i]) {
            touch_states[i] = 1; // Update the state in the passed-in array
        } else {
            touch_states[i] = 0; // Update the state in the passed-in array
        }
    }
}

/* test functions */
void test_calibrate_voltage(){
  int touchPins[NUM_PEOPLE] = {0, 1, 2, 3};
  int touchThresholds[NUM_PEOPLE];

  // TEST 1: threshold computed correctly with moving avg
  Serial.println("[touch_sense.ino] TEST 1: calibrate_voltage thresholds with moving average and constants");
  calibrate_voltage();
  int expectedThresholds[NUM_PEOPLE] = {425, 525, -120, 880};
  for (int i = 0; i < NUM_PEOPLE; i++) { assertBool(touchThresholds[i] == expectedThresholds[i]); }
  
  Serial.println("[touch_sense.ino] all calibrate_voltage unit tests passed!");
}

void test_update_touch_states(){
  int touchPins[NUM_PEOPLE] = {4, 5, 6, 7};
  int touchThresholds[NUM_PEOPLE] = {380, 480, 580, 680}; // Predefined thresholds
  int touch_states[NUM_PEOPLE] = {0, 0, 0, 0}; // Initial states

  // TEST 1: no touch detected for first 2 and touch for last 2
  Serial.println("[touch_sense.ino] TEST 1: update_touch_states");
  update_touch_states(touch_states);
  int expected_touch_states[NUM_PEOPLE] = {0, 0, 1, 1};
  for (int i = 0; i < NUM_PEOPLE; i++) { assertBool(touch_states[i] == expected_touch_states[i]); }

  Serial.println("[touch_sense.ino] all update_touch_states unit tests passed!");
}

#endif

