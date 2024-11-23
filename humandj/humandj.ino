#include "humandj.h"

static bool isReady, signalSent;
static int faderVector[2]; 
static int touchVector[NUM_PEOPLE];
static int midiVector[NUM_PEOPLE];




void setup() {
  // put your setup code here, to run once:
  isReady = false;
  signalSent = false;
  touchVector = {0, 0, 0, 0}; // check_for_change(touchVector, sliderVector, ) 
  midiVector = {0, 0, 0, 0};
  faderVector = {0,0};
}

void loop() {
  // put your main code here, to run repeatedly:

}

bool touch_equals_midi(){
  size = (sizeof(touchVector) / sizeof(touchVector[0]);
  for (int i = 0; i < size; i++) {
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
      init_MIDI();
      calibrate_voltage();
      faderVector = update_fader_states();
      isReady = true; 
      midiVector = {0, 0, 0, 0};
      touchVector = {0, 0, 0, 0};
    }
    else { // transition 1-2
      nextState = sWAIT_FOR_CHANGE;
      light_LED();
    }
    break;
  case sWAIT_FOR_CHANGE:
    if (touch_equals_midi()) { // transition 2-2
      touchVector = update_touch_states();
      faderVector = update_fader_states();
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