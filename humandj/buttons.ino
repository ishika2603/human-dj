/* 
buttons module for ISRs triggered by button presses
*/

void recalibrate_humans() {
  // call calibrate voltage with current values
  calibrate_voltage();
}

void switch_onboard_player() {
  // switches the output device between the onboard player and the DAW via MIDI connection
  if (ONBOARD == true) {
    ONBOARD = false;
  } else {
    ONBOARD = true;
  }
}



