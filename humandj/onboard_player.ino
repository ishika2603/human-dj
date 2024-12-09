#include <"analogWave.h">
/*
* Library to convert MIDI notes to waveforms and send to onboard player.
* Authored by Eva and Komron for HumanDJ capstone component.
*/

#include "analogWave.h"
analogWave wave(DAC);

// MIDI notes for the base notes: C, D, E, F
int PIANO_NOTES[4] = {60, 62, 64, 65};
int CENTRAL_NOTE = 69;
int CENTRAL_FREQUENCY = 440;

void init_onboard_player() {
  wave.begin();
}

bool send_onboard_note(int* touch_states, int* midi_states, int* fader_states) {
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

void play_onboard_note(int note_idx) {
  // calculate the frequency
  // https://en.wikipedia.org/wiki/MIDI_tuning_standard
  // Tom Igoe (https://docs.arduino.cc/tutorials/uno-r4-wifi/dac/)
  int note = PIANO_NOTES[note_idx]
  float frequency = CENTRAL_FREQUENCY * pow(2, ((noteValue - CENTRAL_NOTE) / 12.0));

  // play the note
  wave.freq(int(freq));
}

void stop_onboard_note() {
  // stop the note
  wave.stop();
}