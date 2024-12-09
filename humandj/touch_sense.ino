/*
touch sensing module to calibrate voltage thresholds and update touch states whenever a touch is detected. 
Used within FSM model in humandj.ino to update/initialize variables.
*/

void calibrate_voltage() {
    /*
    Calculates an average voltage read for each human participant. 
    returns: void
    */
    for (int i = 0; i < NUM_PEOPLE; i++) {
      int CALIBRATION_TIMES = 500;
      int totalValue = 0;
      // int totalSquaredValue = 0;
      for (int j = 0; j < CALIBRATION_TIMES; j++) {
        int cur_val = analogRead(touchPins[i]);
        totalValue += cur_val;
        // totalSquaredValue += cur_val * cur_val;
      }

      int initialValue = totalValue / CALIBRATION_TIMES;
      touchThresholds[i] = initialValue - 120;// initialValue - 100; // Set threshold slightly below initial value

      // alternate method is to calculate based on variance/mean etc
      // Compute mean and standard deviation
      // float mean = (float)totalValue / CALIBRATION_TIMES;
      // float variance = ((float)totalSquaredValue / CALIBRATION_TIMES) - (mean * mean);
      // float stddev = sqrt(variance);

      // // Set the threshold slightly below the mean to detect significant dips
      // touchThresholds[i] = mean - (3 * stddev); // Adjust the multiplier as per sensitivity needs

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
    int sensorValue;
    for (int i = 0; i < NUM_PEOPLE; i++) {
        // read 10 times for some person
        int CALIBRATION_TIMES = 500;
        int totalTouchValue = 0;
        for (int j = 0; j < CALIBRATION_TIMES; j++) {
          sensorValue = analogRead(touchPins[i]);
          totalTouchValue += sensorValue;
        }
        // Serial.print("Person");
        // Serial.print(i);
        // Serial.print(":"); 
        // Serial.print(sensorValue); 
        // Serial.print("\t");

        int touchValue = totalTouchValue / CALIBRATION_TIMES;
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

        if (touchValue < touchThresholds[i]) {
            // Serial.print(i);
            // Serial.print(": ");
            // Serial.print(touchValue);
            // Serial.print(" ");
            // Serial.println(touchThresholds[i]);

            touch_states[i] = 1; // Update the state in the passed-in array
            // Serial.print("yes");
            // Serial.print(":"); 
            // Serial.print("\t");

            // Serial.print("Person ");
            // Serial.print(i + 1);
            // Serial.println(" detected!"); // Print message if touch is detected

        } else {
            touch_states[i] = 0; // Update the state in the passed-in array
        }
    }
    Serial.println();
}
