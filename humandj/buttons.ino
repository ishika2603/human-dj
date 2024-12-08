/* 
buttons module for ISRs triggered by button presses

Ways to improve:
* Have it be per-person, instead of everyone at once (too much coordination)
* Have some way to ensure that user-side problems will not break it? 
  (e.g. is there any way we check in the code that you followed instructions, 
  like whether the number is exactly the same)
*/

/*
TODO: add following line to main setup 
attachInterrupt(digitalPinToInterrupt(buttonPin), calibrate_no_touch, RISING);
*/

void calibrate_no_touch_1() {
  // call calibrate voltage with current values
  // assumes that calibrate_voltage takes in a boolean indicating whether this is the contact or no contact signal
  calibrate_voltage(0);
  // Serial.println("no touch 1");
  // digitalWrite(ledPins[0], !ledStates[0]);
  // ledStates[0] = !ledStates[0];
}

void calibrate_no_touch_2() {
  // call calibrate voltage with current values
  // assumes that calibrate_voltage takes in a boolean indicating whether this is the contact or no contact signal
  calibrate_voltage(1);
  // Serial.println("no touch 2");
  // digitalWrite(ledPins[1], LOW);
  // ledStates[1] = !ledStates[1];
}

void calibrate_no_touch_3() {
  // call calibrate voltage with current values
  // assumes that calibrate_voltage takes in a boolean indicating whether this is the contact or no contact signal
  calibrate_voltage(2);
  // Serial.println("no touch 3");
  // digitalWrite(ledPins[2], !ledStates[2]);
  // ledStates[2] = !ledStates[2];
}

void calibrate_no_touch_4() {
  // call calibrate voltage with current values
  // assumes that calibrate_voltage takes in a boolean indicating whether this is the contact or no contact signal
  calibrate_voltage(3);
  // Serial.println("no touch 4");
  // digitalWrite(ledPins[3], !ledStates[3]);
  // ledStates[3] = !ledStates[3];
}

/*
TODO: add following line to main setup 
attachInterrupt(digitalPinToInterrupt(buttonPin), calibrate_touch, RISING);
*/
// void calibrate_touch_1() {
//   // call calibrate voltage with current values
//   // assumes that calibrate_voltage takes in a boolean indicating whether this is the contact or no contact signal
//   // calibrate_voltage(true);
//   // Serial.println("touch 1");
// }

// void calibrate_touch_2() {
//   // call calibrate voltage with current values
//   // assumes that calibrate_voltage takes in a boolean indicating whether this is the contact or no contact signal
//   // calibrate_voltage(true);
//   // Serial.println("touch 2");
// }

// void calibrate_touch_3() {
//   // call calibrate voltage with current values
//   // assumes that calibrate_voltage takes in a boolean indicating whether this is the contact or no contact signal
//   // calibrate_voltage(true);
//   // Serial.println("touch 3");
// }

// void calibrate_touch_4() {
//   // call calibrate voltage with current values
//   // assumes that calibrate_voltage takes in a boolean indicating whether this is the contact or no contact signal
//   // calibrate_voltage(true);
//   // Serial.println("touch 4");
// }

/* Capstone Components */

/*
TODO: add following line to main setup 
attachInterrupt(digitalPinToInterrupt(buttonPin), switch_player, RISING);
*/
void switch_player() {
  // switches a variable indicating where to send the signal on the board.
  onboardDevice = !onboardDevice;
}

