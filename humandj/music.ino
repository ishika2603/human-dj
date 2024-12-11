#include <Control_Surface.h>

// Wiring Guide: https://docs.arduino.cc/built-in-examples/communication/Midi/
// Serial Guide: https://forum.arduino.cc/t/uno-r4-and-serial-rx-tx/1146022/2
// "The separate hardware UART on the RA4M1 is connected to pins 0 and 1 on the UNO R4. You
//  must use the Serial1 object instead of Serial in order to do communication via pins 0 and 1."

// instantiate a serial midi interface at the default midi baud rate
HardwareSerialMIDI_Interface midi {Serial1, MIDI_BAUD};

// limited to 4 base notes that can be indexed
MIDIAddress notes[4] = {MIDI_Notes::C[4], MIDI_Notes::D[4], MIDI_Notes::E[4], MIDI_Notes::F[4]};
const uint8_t velocity = 127;

/*
 * initialize the MIDI interface
 */
void init_MIDI() {
  midi.begin();
}

/*
 * General send_signal function to send a signal to the MIDI interface based on the signal type
 */
bool send_signal(int* touch_states, int* midi_states, int* fader_states) {
    // check for which people the touch states are different from midi states
    for (int i = 0; i < NUM_PEOPLE; i++) {
        // if touch state is same, skip
        if (touch_states[i] == midi_states[i]) { continue; }

        // send the signal based on the touch state
        if (touch_states[i] == 1) {
            send_pitch_bend(fader_states[0]);
            send_play_note(i);
            ledStates[i] = HIGH;
            digitalWrite(ledPins[i], ledStates[i]);
        } else {
            send_stop_note(i);
            ledStates[i] = LOW;
            digitalWrite(ledPins[i], ledStates[i]);
        }

        // update the midi state to match the touch state
        midi_states[i] = touch_states[i];
    }

    // signal sent successfully
    return true;
}

#ifndef TESTING

/*
 * send MIDI pitch bend message to change the pitch of the note
 */
void send_pitch_bend(int analog_pitch) {
    // map the pitch to the range of the pitch bend
    int pitch = map(analog_pitch, 0, 1023, -8192, 0);
    midi.sendPitchBend(Channel_1, pitch);
    midi.update();
}

/*
 * send a MIDI Note On message for the given note to trigger it
 */
void send_play_note(int note_idx) {
    midi.sendNoteOn(notes[note_idx], velocity);  
    midi.update();
}

/*
 * send a MIDI Note Off message to turn it off again
 */
void send_stop_note(int note_idx) {
    midi.sendNoteOff(notes[note_idx], velocity);
    midi.update();
}


/* TESTING MODULE */
#else

/* global variables for mock functions */
int MOCK_NOTES[4] = {1, 2, 3, 4};
int PLAY_VECTOR[4] = {0, 0, 0, 0};

/* mock functions */
void send_pitch_bend(int analog_pitch) {
    // do nothing
}

void send_play_note(int note_idx) {
    for (int i = 0; i < 4; i++) {
        if (PLAY_VECTOR[i] == 0) {
            PLAY_VECTOR[i] = MOCK_NOTES[note_idx];
            break;
        }
    }
}

void send_stop_note(int note_idx) {
    for (int i = 0; i < 4; i++) {
        if (PLAY_VECTOR[i] == 0) {
            PLAY_VECTOR[i] = -1 * MOCK_NOTES[note_idx];
            break;
        }
    }
}

/* test functions */
void test_send_signal() {
    int touch_states[4] = {0, 0, 0, 0};
    int midi_states[4] = {0, 0, 0, 0};
    int fader_states[2] = {0, 0};

    // TEST 1: play no notes
    Serial.println("[music.ino] TEST 1: play no notes");
    send_signal(touch_states, midi_states, fader_states);
    for (int i = 0; i < 4; i++) { assertBool(PLAY_VECTOR[i] == 0); }
    memset(touch_states, 0, sizeof(touch_states)); // reset states
    memset(midi_states, 0, sizeof(midi_states));
    memset(PLAY_VECTOR, 0, sizeof(PLAY_VECTOR));

    // TEST 2: play all notes
    Serial.println("[music.ino] TEST 2: play all notes");
    for (int i = 0; i < 4; i++) { touch_states[i] = 1; } // setup touch states
    send_signal(touch_states, midi_states, fader_states);
    for (int i = 0; i < 4; i++) { assertBool(PLAY_VECTOR[i] == MOCK_NOTES[i]); }
    memset(touch_states, 0, sizeof(touch_states)); // reset states
    memset(midi_states, 0, sizeof(midi_states));
    memset(PLAY_VECTOR, 0, sizeof(PLAY_VECTOR));

    // TEST 3: stop playing all notes
    Serial.println("[music.ino] TEST 3: stop playing all notes");
    for (int i = 0; i < 4; i++) { midi_states[i] = 1; } // setup midi states
    send_signal(touch_states, midi_states, fader_states);
    for (int i = 0; i < 4; i++) { assertBool(PLAY_VECTOR[i] == -1 * MOCK_NOTES[i]); }
    memset(touch_states, 0, sizeof(touch_states)); // reset states
    memset(midi_states, 0, sizeof(midi_states));
    memset(PLAY_VECTOR, 0, sizeof(PLAY_VECTOR));

    // TEST 4: play some notes
    Serial.println("[music.ino] TEST 4: play some notes");
    for (int i = 0; i < 4; i++) { touch_states[i] = i % 2; } // setup touch states
    send_signal(touch_states, midi_states, fader_states);
    assertBool(PLAY_VECTOR[0] == MOCK_NOTES[1]);
    assertBool(PLAY_VECTOR[1] == MOCK_NOTES[3]);
    memset(touch_states, 0, sizeof(touch_states)); // reset states
    memset(midi_states, 0, sizeof(midi_states));
    memset(PLAY_VECTOR, 0, sizeof(PLAY_VECTOR));

    // TEST 5: stop playing some notes
    Serial.println("[music.ino] TEST 5: stop playing some notes");
    for (int i = 0; i < 4; i++) { midi_states[i] = i % 2; } // setup midi states
    send_signal(touch_states, midi_states, fader_states);
    assertBool(PLAY_VECTOR[0] == -1 * MOCK_NOTES[1]);
    assertBool(PLAY_VECTOR[1] == -1 * MOCK_NOTES[3]);
    memset(touch_states, 0, sizeof(touch_states)); // reset states
    memset(midi_states, 0, sizeof(midi_states));
    memset(PLAY_VECTOR, 0, sizeof(PLAY_VECTOR));

    // TEST 6: play some notes and stop playing some notes
    Serial.println("[music.ino] TEST 6: play some notes and stop playing some notes");
    touch_states[0] = 1; touch_states[1] = 1; midi_states[2] = 1; midi_states[3] = 1; // setup states
    send_signal(touch_states, midi_states, fader_states);
    assertBool(PLAY_VECTOR[0] == MOCK_NOTES[0]);
    assertBool(PLAY_VECTOR[1] == MOCK_NOTES[1]);
    assertBool(PLAY_VECTOR[2] == -1 * MOCK_NOTES[2]);
    assertBool(PLAY_VECTOR[3] == -1 * MOCK_NOTES[3]);
    memset(touch_states, 0, sizeof(touch_states)); // reset states
    memset(midi_states, 0, sizeof(midi_states));
    memset(PLAY_VECTOR, 0, sizeof(PLAY_VECTOR));

    Serial.println("[music.ino] all send_signal unit tests passed!");
}


#endif
