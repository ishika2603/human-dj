const int touchPins[] = {A1, A2, A4, A5};
const int NUM_PEOPLE = sizeof(touchPins) / sizeof(touchPins[0]);
int touchThresholds[NUM_PEOPLE]; // store dynamic thresholds for each pin

// uncomment the following for testing
#define TESTING

// ISR related
const int buttonPin = D3;
const int ledPins[] = {D12, D13, D11, D10};
int ledStates[] = {LOW, LOW, LOW, LOW};

const int VOLUME_PIN = A0;
const int PITCH_PIN = A3;

/*
 * Type (enum and struct) definitions for state, orientation,
 * (xy) coordinate, (xyo) coordinate, (upper, lower) bounds
 */
typedef enum {
  sINIT = 1,
  sWAIT_FOR_CHANGE = 2,
  sSEND_SIGNAL = 3,
} state;

// music.ino
void init_MIDI();
bool send_signal(int* touch_states, int* midi_states, int* fader_states);
void send_pitch_bend(int analog_pitch);

// touch_sense.ino
void update_touch_states(int* touch_states);
void calibrate_voltage();

// sliders.ino
void update_fader_states(int* fader_states);

bool touch_equals_midi();
state updateFSM(state curState, int* touchVector, int* faderVector);

/* Capstone */
// uncomment the following line to use the onboard player
// #define ONBOARD
void init_onboard_player();
bool send_onboard_note(int* touch_states, int* midi_states, int* fader_states);

/* Testing */
#ifdef TESTING

// humandj_tests.ino
void assertBool(bool b);

// music.ino
void test_send_signal();

#endif