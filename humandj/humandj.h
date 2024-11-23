

const int touchPins[] = {A3, A5};
const int NUM_PEOPLE = sizeof(touchPins) / sizeof(touchPins[0]);
int touchThresholds[NUM_PEOPLE]; // store dynamic thresholds for each pin

const int PITCH_PIN = A1;
const int VOLUME_PIN = A2;

/*
 * Type (enum and struct) definitions for state, orientation,
 * (xy) coordinate, (xyo) coordinate, (upper, lower) bounds
 */
typedef enum {
  sINIT = 1,
  sWAIT_FOR_CHANGE = 2,
  sSEND_SIGNAL = 3,
} state;

bool touch_equals_midi();
state updateFSM();
