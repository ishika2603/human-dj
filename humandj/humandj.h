

const int touchPins[] = {A3, A5};
const int NUM_PEOPLE = sizeof(touchPins) / sizeof(touchPins[0]);
int touchThresholds[NUM_PEOPLE]; // store dynamic thresholds for each pin

/*
 * Type (enum and struct) definitions for state, orientation,
 * (xy) coordinate, (xyo) coordinate, (upper, lower) bounds
 */
typedef enum {
  sINIT = 1,
  sWAIT_FOR_CHANGE = 2,
  sSEND_START_NOTE = 3,
  sSEND_END_NOTE = 4,
  sSEND_SLIDER_CHANGE = 5,
} state;


state updateFSM();
