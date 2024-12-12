/*
 * For human dj fsm testing
 */
#ifdef TESTING

/*        
 * Helper function for printing states
 */
char* s2str(state s) {
  switch(s) {
    case sINIT:
        return "(1) INIT";
    case sWAIT_FOR_CHANGE:
        return "(2) WAIT_FOR_CHANGE";
    case sSEND_SIGNAL:
        return "(3) SEND_SIGNAL";
    default:
        return "INVALID_STATE";
  }
}

/*
 * Helper function for printing arrays
 */
void printArray(int* arr, int size) {
    Serial.print("[");
    for (int i = 0; i < size; i++) {
        Serial.print(arr[i]);

        if (i != size - 1) {
            Serial.print(", ");
        }
    }
    Serial.print("]");
}

/*
 * Helper function for asserting values
 */
void assertBool(bool b) {
    if (!b) {
        Serial.println("Assertion failed!");
        while (true); // hang if assertion fails
    }
}


/*
 * Test for FSM transitions
 */
bool testTransition(state startState,
                    state endState,
                    state_inputs testStateInputs, 
                    state_vars startStateVars,
                    state_vars endStateVars) {
    // set variables
    for (int i = 0; i < NUM_PEOPLE; i++) {
        midiVector[i] = startStateVars.midi_states[i];
    }
    signalSent = startStateVars.signal_sent;

    // run the FSM
    state resultState = updateFSM(startState, testStateInputs.touch_states, testStateInputs.fader_states);

    // check the results
    bool passed_test = ((resultState == endState) and (signalSent == endStateVars.signal_sent));
    for (int i = 0; i < NUM_PEOPLE; i++) {
        passed_test = passed_test and (midiVector[i] == endStateVars.midi_states[i]);
    }

    if (passed_test) {
        Serial.print("[FSM] test from ");
        Serial.print(s2str(startState));
        Serial.print(" to ");
        Serial.print(s2str(endState));
        Serial.println(" passed");
    } else {
        Serial.print("[FSM] test from ");
        Serial.print(s2str(startState));
        Serial.print(" to ");
        Serial.print(s2str(endState));
        Serial.println(" failed");
    }

    #ifdef DEBUG

    if (!passed_test) {
        // print out the states
        Serial.print("> end state expected: ");
        Serial.print(s2str(endState));
        Serial.print(" but got: ");
        Serial.println(s2str(resultState));

        // print out the inputs
        Serial.print("> inputs:   touch_states: ");
        printArray(testStateInputs.touch_states, NUM_PEOPLE);
        Serial.print(" | fader_states: ");
        printArray(testStateInputs.fader_states, 2);
        Serial.println();
        
        // print out the variables
        Serial.print("> expected: midi_states: ");
        printArray(endStateVars.midi_states, NUM_PEOPLE);
        Serial.print(" | signal_sent: ");
        Serial.print(endStateVars.signal_sent);
        Serial.println();
        Serial.print("> actual:   midi_states: ");
        printArray(midiVector, NUM_PEOPLE);
        Serial.print(" | signal_sent: ");
        Serial.print(signalSent);
        Serial.println();
    }
    #endif

    return passed_test;
}

const int numTests = 1;
const state testStatesIn[numTests] = {sINIT};
const state testStatesOut[numTests] = {sWAIT_FOR_CHANGE};
const state_inputs testInputs[numTests] = {0};
const state_vars testVarsIn[numTests] = {0};
const state_vars testVarsOut[numTests] = {0};


/*
 * Runs through all the FSM tests
 */
void testAllTests() {
    Serial.println("Running all FSM tests...");

    for (int i = 0; i < numTests; i++) {
        if (!testTransition(testStatesIn[i], testStatesOut[i], testInputs[i], testVarsIn[i], testVarsOut[i])) {
            while (true); // hang if test fails
        }
    }
    Serial.println("[FSM] all tests passed!");
}

/*
 * Runs all the unit tests
 */
void runUnitTests() {
    Serial.println("Running all unit tests...");
    test_send_signal();
    test_send_onboard_note();
    test_update_fader_states();
    test_calibrate_voltage();
    test_update_touch_states();
}

#endif
