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
  calibrate_voltage(0, false);
}

void calibrate_no_touch_2() {
  // call calibrate voltage with current values
  // assumes that calibrate_voltage takes in a boolean indicating whether this is the contact or no contact signal
  calibrate_voltage(1, false);
}

void calibrate_no_touch_3() {
  // call calibrate voltage with current values
  // assumes that calibrate_voltage takes in a boolean indicating whether this is the contact or no contact signal
  calibrate_voltage(2, false);
}

void calibrate_no_touch_4() {
  // call calibrate voltage with current values
  // assumes that calibrate_voltage takes in a boolean indicating whether this is the contact or no contact signal
  calibrate_voltage(3, false);
}

/*
TODO: add following line to main setup 
attachInterrupt(digitalPinToInterrupt(buttonPin), calibrate_touch, RISING);
*/
void calibrate_touch() {
  // call calibrate voltage with current values
  // assumes that calibrate_voltage takes in a boolean indicating whether this is the contact or no contact signal
  calibrate_voltage(true);
}

/*
TODO: add following line to main setup 
attachInterrupt(digitalPinToInterrupt(buttonPin), switch_player, RISING);
*/
void switch_player() {
  // switches a macro indicating where to send the signal on the board.
  return;
}

