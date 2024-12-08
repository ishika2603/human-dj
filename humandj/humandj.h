const int touchPins[] = {A3, A5};
const int NUM_PEOPLE = sizeof(touchPins) / sizeof(touchPins[0]);
int touchThresholds[NUM_PEOPLE]; // store dynamic thresholds for each pin

// ISR related
const int buttonPins[] = {D3, D4, D5, D6};
const int ledPins[] = {D9, D10, D11, D12};
int ledStates[] = {LOW, LOW, LOW, LOW};


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
state updateFSM(state curState);


/* Capstone Components */
void onboard_player(int* touch_states, int* midi_states, int* fader_states);

int onboardDevice = 0;
void (*outputFunctions[])(void) = {send_signal,  onboard_player};
