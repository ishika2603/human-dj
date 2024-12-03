/*
sliders module for any slider logic!
*/

void update_fader_states(int* fader_states){
    /*
    Updates the pitch and volume information in the fader states to the values 
    read from the potentiometer sliders. fader_states are defined to be on a scale
    of 0 to 100 value so need to map ADC logic to that.

    returns: void
    */

    // dac values between 0 to 1023
    int pitch_dac = analogRead(PITCH_PIN);
    int volume_dac = analogRead(VOLUME_PIN);

    fader_states[0] = pitch_dac;
    fader_states[1] = volume_dac;
}

