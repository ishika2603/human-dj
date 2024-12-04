/*
touch sensing module to calibrate voltage thresholds and update touch states whenever a touch is detected. 
Used within FSM model in humandj.ino to update/initialize variables.
*/

void calibrate_voltage() {
    /*
    Calculates an average voltage read for each human participant. 
    returns: void
    */
    delay(100);
    for (int i = 0; i < NUM_PEOPLE; i++) {
      int CALIBRATION_TIMES = 500;
      int totalValue = 0;
      for (int j = 0; j < CALIBRATION_TIMES; j++) {
        totalValue += analogRead(touchPins[i]);
      }

      int initialValue = totalValue / CALIBRATION_TIMES;
      touchThresholds[i] = initialValue - 60;// initialValue - 100; // Set threshold slightly below initial value
      Serial.print("Calibrated threshold for Person ");
      Serial.print(i + 1);
      Serial.print(": ");
      Serial.println(touchThresholds[i]);
      
    }
    Serial.println();

}

void update_touch_states(int* touch_states) {
    /*
    Updates the touch states based on who the DJ is currently touching / or not touching.
    returns: void
    */

    for (int i = 0; i < NUM_PEOPLE; i++) {
        // read 10 times for some person
        int CALIBRATION_TIMES = 500;
        int totalTouchValue = 0;
        for (int j = 0; j < CALIBRATION_TIMES; j++) {
          totalTouchValue += analogRead(touchPins[i]);
        }
        int touchValue = totalTouchValue / CALIBRATION_TIMES;
      
        if (i == 0) {
          Serial.println(touchValue);
        }

        if (touchValue < touchThresholds[i]) {
            // Serial.print(i);
            // Serial.print(": ");
            // Serial.print(touchValue);
            // Serial.print(" ");
            // Serial.println(touchThresholds[i]);

            touch_states[i] = 1; // Update the state in the passed-in array

            // Serial.print("Person ");
            // Serial.print(i + 1);
            // Serial.println(" detected!"); // Print message if touch is detected

        } else {
            touch_states[i] = 0; // Update the state in the passed-in array
        }
    }
}


