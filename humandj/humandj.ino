#include "humandj.h"

static bool isReady, signalSent;
static int faderVector[2]; 
static int touchVector[NUM_PEOPLE];
static int midiVector[NUM_PEOPLE];


void setup() {
  // put your setup code here, to run once:
  isReady = false;
  signalSent = false;
  memset(touchVector, 0, sizeof(touchVector));  // check_for_change(touchVector, sliderVector, ) 
  memset(midiVector, 0, sizeof(midiVector));
  memset(faderVector, 0, sizeof(faderVector));

  // does not compile:
  // touchVector = {0, 0, 0, 0};
  // midiVector = {0, 0, 0, 0};
  // faderVector = {0,0};
}

void loop() {
  // put your main code here, to run repeatedly:

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
      }
      break;
    return nextState;
  }
}