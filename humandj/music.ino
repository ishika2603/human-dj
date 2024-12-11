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

// initialize the MIDI interface
void init_MIDI() {
    midi.begin();
}

// general send_signal function to send a signal to the MIDI interface based on the signal type
bool send_signal(int* touch_states, int* midi_states, int* fader_states) {
    // check for which people the touch states are different from midi states
    for (int i = 0; i < NUM_PEOPLE; i++) {

        // if touch state is same, skip
        if (touch_states[i] == midi_states[i]) { continue; }

        // send the signal based on the touch state
        if (touch_states[i] == 1) {
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

// send MIDI pitch bend message to change the pitch of the note
void send_pitch_bend(int analog_pitch) {
    // map the pitch to the range of the pitch bend
    // FIXME: look up the range of pitch bend, and how to map it
    int pitch = map(pitch, 0, 1023, -8192, 8191);
    midi.sendPitchBend(Channel_1, pitch);
    midi.update();
}

// send a MIDI Note On message for the given note to trigger it
void send_play_note(int note_idx) {
    midi.sendNoteOn(notes[note_idx], velocity);  
    midi.update();
}

// send a MIDI Note Off message to turn it off again
void send_stop_note(int note_idx) {
    midi.sendNoteOff(notes[note_idx], velocity);
    midi.update();
}
