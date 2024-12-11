/*
* Library to convert MIDI notes to waveforms and send to onboard player.
* Authored by Eva and Komron for HumanDJ capstone component.
*/

#include "analogWave.h"
analogWave wave(DAC);

// MIDI notes for the base notes: C, D, E, F
const int PIANO_NOTES[4] = {70, 75, 80, 85};
const int CENTRAL_NOTE = 69;
const int CENTRAL_FREQUENCY = 440;
int PITCH_BEND = 0;

void init_onboard_player() {
    wave.sine(10);
}

bool send_onboard_note(int* touch_states, int* midi_states, int* fader_states) {
    onboard_pitch_bend(fader_states[0]);

    for (int i = 0; i < NUM_PEOPLE; i++) {
        // if touch state is same, skip
        if (touch_states[i] == midi_states[i]) { continue; }

        if (touch_states[i] == 1) {
            // send the signal based on the touch state
            play_onboard_note(i);

            ledStates[i] = HIGH;
            digitalWrite(ledPins[i], ledStates[i]);
        } else {
            stop_onboard_note(i);

            ledStates[i] = LOW;
            digitalWrite(ledPins[i], ledStates[i]);
        }

        // update the midi state to match the touch state
        midi_states[i] = touch_states[i];
    }

    return true;
}

#ifndef TESTING

void onboard_pitch_bend(int analog_pitch) {
    PITCH_BEND = map(analog_pitch, 0, 1023, 0, 200);
}

void play_onboard_note(int note_idx) {
    // calculate the frequency
    // https://en.wikipedia.org/wiki/MIDI_tuning_standard
    // Tom Igoe (https://docs.arduino.cc/tutorials/uno-r4-wifi/dac/)
    int note = PIANO_NOTES[note_idx];
    float frequency = CENTRAL_FREQUENCY * pow(2, ((note - CENTRAL_NOTE) / 12.0));
    // play the note
    wave.freq(int(frequency) + PITCH_BEND);
}

void stop_onboard_note(int note_idx) {
  // stop the note
  wave.stop();
}

/* TESTING MODULE */
#else

/* global variables for mock functions */
int MOCK_ONBOARD_NOTES[4] = {1, 2, 3, 4};
int PLAY_ONBOARD_VECTOR[4] = {0, 0, 0, 0};
int MOCK_PITCH_BEND = 0;

/* mock functions */
void onboard_pitch_bend(int analog_pitch) {
    MOCK_PITCH_BEND = analog_pitch;
}

void play_onboard_note(int note_idx) {
    for (int i = 0; i < 4; i++) {
        if (PLAY_ONBOARD_VECTOR[i] == 0) {
            PLAY_ONBOARD_VECTOR[i] = MOCK_NOTES[note_idx];
            break;
        }
    }
}

void stop_onboard_note(int note_idx) {
    memset(PLAY_ONBOARD_VECTOR, 0, sizeof(PLAY_ONBOARD_VECTOR));
}

/* test functions */
void test_send_onboard_note() {
    int touch_states[4] = {0, 0, 0, 0};
    int midi_states[4] = {0, 0, 0, 0};
    int fader_states[2] = {0, 0};

    // TEST 1: play no notes
    Serial.println("[onboard_player.ino] TEST 1: play no notes");
    send_onboard_note(touch_states, midi_states, fader_states);
    for (int i = 0; i < 4; i++) { assertBool(PLAY_ONBOARD_VECTOR[i] == 0); }
    memset(touch_states, 0, sizeof(touch_states)); // reset states
    memset(midi_states, 0, sizeof(midi_states));
    memset(PLAY_ONBOARD_VECTOR, 0, sizeof(PLAY_ONBOARD_VECTOR));

    // TEST 2: play all notes
    Serial.println("[onboard_player.ino] TEST 2: play all notes");
    for (int i = 0; i < 4; i++) { touch_states[i] = 1; } // setup touch states
    send_onboard_note(touch_states, midi_states, fader_states);
    for (int i = 0; i < 4; i++) { assertBool(PLAY_ONBOARD_VECTOR[i] == MOCK_ONBOARD_NOTES[i]); }
    memset(touch_states, 0, sizeof(touch_states)); // reset states
    memset(midi_states, 0, sizeof(midi_states));
    memset(PLAY_ONBOARD_VECTOR, 0, sizeof(PLAY_ONBOARD_VECTOR));

    // TEST 3: stop playing all notes
    Serial.println("[onboard_player.ino] TEST 3: stop playing all notes");
    for (int i = 0; i < 4; i++) { midi_states[i] = 1; } // setup midi states
    send_onboard_note(touch_states, midi_states, fader_states);
    for (int i = 0; i < 4; i++) { assertBool(PLAY_ONBOARD_VECTOR[i] == 0); }
    memset(touch_states, 0, sizeof(touch_states)); // reset states
    memset(midi_states, 0, sizeof(midi_states));
    memset(PLAY_ONBOARD_VECTOR, 0, sizeof(PLAY_ONBOARD_VECTOR));

    // TEST 4: play one note
    Serial.println("[onboard_player.ino] TEST 4: play one note");
    touch_states[0] = 1;
    send_onboard_note(touch_states, midi_states, fader_states);
    assertBool(PLAY_ONBOARD_VECTOR[0] == MOCK_ONBOARD_NOTES[0]);
    memset(touch_states, 0, sizeof(touch_states)); // reset states
    memset(midi_states, 0, sizeof(midi_states));
    memset(PLAY_ONBOARD_VECTOR, 0, sizeof(PLAY_ONBOARD_VECTOR));

    // TEST 5: play two notes, stop one
    Serial.println("[onboard_player.ino] TEST 5: play two notes, stop one");
    touch_states[0] = 1;
    touch_states[1] = 1;
    midi_states[2] = 1;
    send_onboard_note(touch_states, midi_states, fader_states);
    for (int i = 0; i < 2; i++) { assertBool(PLAY_ONBOARD_VECTOR[i] == 0); }
    memset(touch_states, 0, sizeof(touch_states)); // reset states
    memset(midi_states, 0, sizeof(midi_states));
    memset(PLAY_ONBOARD_VECTOR, 0, sizeof(PLAY_ONBOARD_VECTOR));

    // TEST 6: change pitch bend
    Serial.println("[onboard_player.ino] TEST 6: change pitch bend");
    fader_states[0] = 1023;
    send_onboard_note(touch_states, midi_states, fader_states);
    assertBool(MOCK_PITCH_BEND == 1023);
    memset(fader_states, 0, sizeof(fader_states)); // reset states
    MOCK_PITCH_BEND = 0;

    // TEST 7: do not change pitch bend
    Serial.println("[onboard_player.ino] TEST 7: do not change pitch bend");
    send_onboard_note(touch_states, midi_states, fader_states);
    assertBool(MOCK_PITCH_BEND == 0);

    Serial.println("[onboard_player.ino] all send_onboard_note tests passed!");

}

#endif