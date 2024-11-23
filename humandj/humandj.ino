#include "humandj.h"
#include <Control_Surface.h>

const int touchPins[] = {A3, A5};
const int numPeople = sizeof(touchPins) / sizeof(touchPins[0]);
int touchThresholds[numPeople]; // store dynamic thresholds for each pin
int touchStatus[numPeople]; // store current touch status (0 or 1)

HardwareSerialMIDI_Interface midi {Serial1, MIDI_BAUD};
const uint8_t velocity = 127;

static bool isReady, newTouch, stopTouch, signalSent;
static int sliderChange[2]; 




void setup() {
  // put your setup code here, to run once:
  isReady = false;
  newTouch = false;
  stopTouch = false;
  touchVector = {0, 0, 0, 0}; // check_for_change(touchVector, sliderVector, ) 
  signalSent = false;
  sliderChange = {0,0};
}

void loop() {
  // put your main code here, to run repeatedly:

}

state updateFSM(state curState) {
  state nextState;

  switch(curState) {
  case sINIT:
    if (!isReady) { // transition 1-1
      init_MIDI();
      calibrate_voltage();
      init_sliders();
      isReady = true; 
    }
    else { // transition 1-2
      newTouch = false;
      stopTouch = false;
      sliderChange = {0,0};

    }
    break;
  case sWAIT_FOR_CHANGE:
    if ((newTouch ==false)&&(stopTouch == false)&&(sliderChange[0] == 0) && (sliderChange[1] == 0)) { // transition 2-2
      check_for_change();
    }
    else if (newTouch) { // transition 2-3

    }
    else if () { // transition 2-4

    }
    else if () { // transition 2-5

    }
    else{

    }
    break;
  case sSEND_START_NOTE:
    if () { // transition 3-2

    }
    else if () { // transition 3-3

    }
    }else{

    }
    // add else if/else
    break;

  case sSEND_END_NOTE:
    if () { // transition 4-2

    }
    else if () { // transition 4-4

    }
    }else{

    }
    // add else if/else
    break;
  case sSEND_SLIDER_CHANGE:
    if () { // transition 5-2

    }
    else if () { // transition 5-5

    }
    }else{

    }
    // add else if/else
    break;
  return nextState;
}