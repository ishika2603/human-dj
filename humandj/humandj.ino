#include "humandj.h"

static bool signalSent;
static int faderVector[2]; 
static int touchVector[NUM_PEOPLE];
static int midiVector[NUM_PEOPLE];

void setup() {
    // put your setup code here, to run once:
    Serial.begin(9600);
    memset(touchVector, 0, sizeof(touchVector));  // check_for_change(touchVector, sliderVector, ) 
    memset(midiVector, 0, sizeof(midiVector));
    memset(faderVector, 0, sizeof(faderVector));
    signalSent = false;

    pinMode(ledPins[0], OUTPUT);
    pinMode(ledPins[1], OUTPUT);
    pinMode(ledPins[2], OUTPUT);
    pinMode(ledPins[3], OUTPUT);

    attachInterrupt(digitalPinToInterrupt(buttonPin), recalibrate_humans, RISING);
    attachInterrupt(digitalPinToInterrupt(onboardPin), switch_onboard_player, RISING);

    #ifdef TESTING
    
    testAllTests();
    runUnitTests();

    #else

    initWDT();
    Serial.println("Setup done!");

    #endif
}

void loop() {
    // put your main code here, to run repeatedly:
    #ifndef TESTING
    static state CURRENT_STATE = sINIT;

    petWDT();
    CURRENT_STATE = updateFSM(CURRENT_STATE, touchVector, faderVector);
    delay(10);

    #endif
}

bool touch_equals_midi(int* touch_states) {
    for (int i = 0; i < NUM_PEOPLE; i++) {
        if (touch_states[i] != midiVector[i]) {
            return false; // If any element is different, the vectors are not equal
        }
    }
    return true;
}


state updateFSM(state curState, int* touchVector, int* faderVector) {
    state nextState;

    switch(curState) {
        case sINIT: // transition 1-2
            memset(touchVector, 0, sizeof(touchVector));
            memset(midiVector, 0, sizeof(midiVector));
            signalSent = false;
            calibrate_voltage();
            init_onboard_player();
            init_MIDI();
            update_fader_states(faderVector);

            // blink the LEDs
            for (int i = 0; i < NUM_PEOPLE; i++) {
                ledStates[i] = HIGH;
                digitalWrite(ledPins[i], ledStates[i]);
            }
            delay(500);
            for (int i = 0; i < NUM_PEOPLE; i++) {
                ledStates[i] = LOW;
                digitalWrite(ledPins[i], ledStates[i]);
            }
            nextState = sWAIT_FOR_CHANGE;
            break;

        case sWAIT_FOR_CHANGE:
            if (touch_equals_midi(touchVector)) { // transition 2-2
                update_touch_states(touchVector);
                update_fader_states(faderVector);
                nextState = sWAIT_FOR_CHANGE;
            } else { // transition 2-3
                signalSent = false;
                nextState = sSEND_SIGNAL;
            }
            break;

        case sSEND_SIGNAL:
            if (signalSent) { // transition 3-2
                nextState = sWAIT_FOR_CHANGE;
            } else { // transition 3-3
                if (ONBOARD) {
                    signalSent = send_onboard_note(touchVector, midiVector, faderVector);
                } else {
                    signalSent = send_signal(touchVector, midiVector, faderVector);
                }
                nextState = sSEND_SIGNAL;
            }
            break;
    }

    return nextState;
}