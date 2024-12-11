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

  attachInterrupt(digitalPinToInterrupt(buttonPin), calibrate_no_touch, RISING);
  
  #ifdef TESTING

  // estAllTests(); // for fsm testing
  runUnitTests();

  #else

  Serial.println("setup done");
  
  #endif
}

void loop() {
  // put your main code here, to run repeatedly:
  #ifndef TESTING
  static state CURRENT_STATE = sINIT;
  CURRENT_STATE = updateFSM(CURRENT_STATE, touchVector, faderVector);
  delay(10);
  
  #endif
}

bool touch_equals_midi() {
  for (int i = 0; i < NUM_PEOPLE; i++) {
        if (touchVector[i] != midiVector[i]) {
            return false; // If any element is different, the vectors are not equal
        }
    }
    return true;
}


state updateFSM(state curState, int* touchVector, int* faderVector) {
  state nextState;

  switch(curState) {
    case sINIT:
      if (!isReady) { // transition 1-1
        memset(touchVector, 0, sizeof(touchVector));
        memset(midiVector, 0, sizeof(midiVector));
        calibrate_voltage();
        #ifdef ONBOARD
          init_onboard_player();
        #else 
          init_MIDI();
        #endif
        update_fader_states(faderVector);
        isReady = true; 
        nextState = sINIT;
      }
      else { // transition 1-2
        nextState = sWAIT_FOR_CHANGE;
        for (int i = 0; i < NUM_PEOPLE; i++) {
          ledStates[i] = HIGH;
          digitalWrite(ledPins[i], ledStates[i]);
        }
        delay(500);
        for (int i = 0; i < NUM_PEOPLE; i++) {
          ledStates[i] = LOW;
          digitalWrite(ledPins[i], ledStates[i]);
        }
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
        #ifdef ONBOARD
          signalSent = send_onboard_note(touchVector, midiVector, faderVector);
        #else
          signalSent = send_signal(touchVector, midiVector, faderVector);
        #endif
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