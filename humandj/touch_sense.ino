

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
    returns: touch_states
    */

    for (int i = 0; i < numPeople; i++) {
    int touchValue = analogRead(touchPins[i]); // Read value from each sensor

    if (touchValue < touchThresholds[i]) {
    touchStatus[i] = 1;

    Serial.print("Person ");
    Serial.print(i + 1);
    Serial.println(" detected!"); // Print message if touch is detected

    midi.sendNoteOn(MIDI_Notes::C[i], velocity);  
    }
    else{
    touchStatus[i] = 0;
    midi.sendNoteOff(MIDI_Notes::C[i], velocity);  
    } 
    }


}


