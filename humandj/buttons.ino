/* 
buttons module for ISRs triggered by button presses
*/

void recalibrate_humans() {
  // call calibrate voltage with current values
  // assumes that calibrate_voltage takes in a boolean indicating whether this is the contact or no contact signal
  calibrate_voltage();
}

void switch_onboard_player() {
  // call calibrate voltage with current values
  // assumes that calibrate_voltage takes in a boolean indicating whether this is the contact or no contact signal
  if (ONBOARD == true) {
    ONBOARD = false;
  } else {
    ONBOARD = true;
  }
}



