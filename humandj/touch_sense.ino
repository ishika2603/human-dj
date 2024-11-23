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
    int initialValue = analogRead(touchPins[i]);
    touchThresholds[i] = initialValue - 100; // Set threshold slightly below initial value
    Serial.print("Calibrated threshold for Person ");
    Serial.print(i + 1);
    Serial.print(": ");
    Serial.println(touchThresholds[i]);
    }

}

void update_touch_states(int* touch_states) {
    /*
    Updates the touch states based on who the DJ is currently touching / or not touching.
    returns: void
    */

    for (int i = 0; i < NUM_PEOPLE; i++) {
        int touchValue = analogRead(touchPins[i]); // Read value from each sensor

        if (touchValue < touchThresholds[i]) {
            touch_states[i] = 1; // Update the state in the passed-in array

            Serial.print("Person ");
            Serial.print(i + 1);
            Serial.println(" detected!"); // Print message if touch is detected

        } else {
            touch_states[i] = 0; // Update the state in the passed-in array
        }
    }
}


