#include <Control_Surface.h>

// wiring: https://docs.arduino.cc/built-in-examples/communication/Midi/

// https://forum.arduino.cc/t/uno-r4-and-serial-rx-tx/1146022/2
// "The separate hardware UART on the RA4M1 is connected to pins 0 and 1 on the UNO R4. You
//  must use the Serial1 object instead of Serial in order to do communication via pins 0 and 1."

// instantiate a serial midi interface at the default midi baud rate
HardwareSerialMIDI_Interface midi {Serial1, MIDI_BAUD};

void setup() {
    midi.begin(); // init the MIDI interface
}

// specify the MIDI note number to trigger, and the velocity with which to 
// trigger it
const MIDIAddress note = MIDI_Notes::C[4]; // C4 is middle C
const uint8_t velocity = 127;              // 127 is maximum velocity

void loop() {
    // Send a MIDI Note On message for the given note to trigger it
    midi.sendNoteOn(note, velocity);  
    delay(2000);
    // Send a MIDI Note Off message to turn it off again
    midi.sendNoteOff(note, velocity);
    delay(500);
    
    midi.update();
}