#include "humandj.h"

static bool isReady, signalSent;
static int faderVector[2]; 
static int touchVector[NUM_PEOPLE];
static int midiVector[NUM_PEOPLE];


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  isReady = false;
  signalSent = false;
  memset(touchVector, 0, sizeof(touchVector));  // check_for_change(touchVector, sliderVector, ) 
  memset(midiVector, 0, sizeof(midiVector));
  memset(faderVector, 0, sizeof(faderVector));

  // testing for ISR functionality
  pinMode(ledPins[0], OUTPUT);
  pinMode(ledPins[1], OUTPUT);
  pinMode(ledPins[2], OUTPUT);
  pinMode(ledPins[3], OUTPUT);

  pinMode(buttonPins[0], INPUT);
  pinMode(buttonPins[1], INPUT);
  pinMode(buttonPins[2], INPUT);
  pinMode(buttonPins[3], INPUT);

  digitalWrite(buttonPins[0], LOW);
  digitalWrite(buttonPins[1], LOW);
  digitalWrite(buttonPins[2], LOW);
  digitalWrite(buttonPins[3], LOW);
  
  for (int i = 0; i < 4; i++) {
    ledStates[i] = HIGH;
    digitalWrite(ledPins[i], ledStates[i]);
    // delay()
    // ledStates[i] = LOW;

  }

  Serial.println("LEDs DONE");

  

  // attachInterrupt(digitalPinToInterrupt(buttonPins[0]), calibrate_touch_1, FALLING);
  // attachInterrupt(digitalPinToInterrupt(buttonPins[1]), calibrate_touch_2, RISING);
  // attachInterrupt(digitalPinToInterrupt(buttonPins[2]), calibrate_touch_3, RISING);
  // attachInterrupt(digitalPinToInterrupt(buttonPins[3]), calibrate_touch_4, RISING);

  attachInterrupt(digitalPinToInterrupt(buttonPins[0]), calibrate_no_touch_1, FALLING);
  attachInterrupt(digitalPinToInterrupt(buttonPins[1]), calibrate_no_touch_1, FALLING);
  attachInterrupt(digitalPinToInterrupt(buttonPins[2]), calibrate_no_touch_1, RISING);
  attachInterrupt(digitalPinToInterrupt(buttonPins[3]), calibrate_no_touch_1, RISING);

  // does not compile:
  // touchVector = {0, 0, 0, 0};
  // midiVector = {0, 0, 0, 0};
  // faderVector = {0,0};
  
  Serial.println("setup done");

  
}

void loop() {
  // put your main code here, to run repeatedly:
  static state CURRENT_STATE = sINIT;
  CURRENT_STATE = updateFSM(CURRENT_STATE);
  delay(10);
}

bool touch_equals_midi() {
  for (int i = 0; i < NUM_PEOPLE; i++) {
        if (touchVector[i] != midiVector[i]) {
            return false; // If any element is different, the vectors are not equal
        }
    }
    return true;
}


state updateFSM(state curState) {
  state nextState;

  switch(curState) {
    case sINIT:
      if (!isReady) { // transition 1-1
        memset(touchVector, 0, sizeof(touchVector));
        memset(midiVector, 0, sizeof(midiVector));

        init_MIDI();
        calibrate_voltage();
        update_fader_states(faderVector);
        isReady = true; 
        nextState = sINIT;
      }
      else { // transition 1-2
        nextState = sWAIT_FOR_CHANGE;
        // light_LED(); FIXME: add functionalit
      }
      break;
    case sWAIT_FOR_CHANGE:
      if (touch_equals_midi()) { // transition 2-2
        update_touch_states(touchVector);
        update_fader_states(faderVector);
        nextState = sWAIT_FOR_CHANGE;
      }
      else{
        signalSent = false;
        nextState = sSEND_SIGNAL;
      }
      break;
    case sSEND_SIGNAL:
      if (signalSent) { // transition 3-2
        nextState = sWAIT_FOR_CHANGE;
      }
      else{ // transition 3-3
        signalSent = send_signal(touchVector, midiVector, faderVector);
        nextState = sSEND_SIGNAL;
      }
      break;
  }

  // if (nextState != curState) {
  //   Serial.print("New State: ");
  //   Serial.println(nextState);
  // }
  return nextState;
}