// uncomment the following for testing
#define TESTING

// uncomment the following for debugging information
#define DEBUG

// pin definitions
int touchPins[] = {A1, A2, A4, A5};
const int buttonPin = D2;
const int ledPins[] = {D12, D13, D11, D10};

const int VOLUME_PIN = A0;
const int PITCH_PIN = A3;

// participants and dynamic thresholds thresholds
const int NUM_PEOPLE = sizeof(touchPins) / sizeof(touchPins[0]);
int touchThresholds[NUM_PEOPLE];

// ISR related
int ledStates[] = {LOW, LOW, LOW, LOW};


/*
 * Type for the state of the FSM
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

// humandj.ino
bool touch_equals_midi();
state updateFSM(state curState, int* touchVector, int* faderVector);

// buttons.ino
void recalibrate_humans();
void switch_onboard_player();

// watchdog.ino
unsigned int getNextCPUINT(unsigned int start);
void initWDT();
void petWDT();
void wdtISR();

/* Capstone */
int onboardPin = D3;
bool ONBOARD = false;
void init_onboard_player();
bool send_onboard_note(int* touch_states, int* midi_states, int* fader_states);

/* Testing */
#ifdef TESTING

/*
 * Type for the inputs to the FSM
 */
typedef struct {
    int touch_states[NUM_PEOPLE];
    int fader_states[2];
} state_inputs;

/*
 * Type for the variables of the FSM
 */
typedef struct {
    int midi_states[NUM_PEOPLE];
    bool signal_sent;
} state_vars;

// humandj_tests.ino
void assertBool(bool b);
void runUnitTests();
void testAllTests();

// music.ino
void test_send_signal();

// sliders.ino
void test_update_fader_states();

// onboard_player.ino
void test_send_onboard_note();

#endif