/*
sliders module for any slider logic!
*/

#ifndef TESTING

int customAnalogRead(int pin) {
  /*
  Wrapper function for analogRead for testing purposes. 
  For typical functionality, acts as normal analogRead.
  */
  return analogRead(pin);
}

#else

int customAnalogRead(int pin) {
  /*
  Wrapper function for analogRead for testing purposes. 
  For typical functionality, acts as normal analogRead.
  */
  if (pin == PITCH_PIN) return 111;
  if (pin == VOLUME_PIN) return 222;
  return -1;
  
}

#endif

void update_fader_states(int* fader_states){
    /*
    Updates the pitch and volume information in the fader states to the values 
    read from the potentiometer sliders. fader_states are defined to be on a scale
    of 0 to 100 value so need to map ADC logic to that.

    returns: void
    */

    // dac values between 0 to 1023
    int pitch_dac = customAnalogRead(PITCH_PIN);
    int volume_dac = customAnalogRead(VOLUME_PIN);

    fader_states[0] = pitch_dac;
    fader_states[1] = volume_dac;
}

#ifdef TESTING

void test_update_fader_states() {
  int fader_states[2] = {0, 0};
  update_fader_states(fader_states);
  Serial.println("[sliders.ino] TEST 1: confirm pitch updates correctly");
  assertBool(fader_states[0] == 111);
  Serial.println("[sliders.ino] TEST 2: confirm volume updates correctly");
  assertBool(fader_states[1] == 222);
  Serial.println("[sliders.ino] all update_fader_states unit tests passed!");
}

#endif


