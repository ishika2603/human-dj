/*
 * For human dj fsm testing
 */

/*        
 * Helper function for printing states
 */
char* s2str(state s) {
  switch(s) {
    case sINIT:
        return "(1) INIT";
    case sWAIT_FOR_CHANGE:
        return "(2) WAIT_FOR_CHANGET";
    case sSEND_SIGNAL:
        return "(3) sSEND_SIGNAL";
    default:
        return "???";
  }
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


/*
 * Test for FSM transitions
 */
bool testTransition(state startState,
                    state endState,
                    state_inputs testStateInputs, 
                    state_vars startStateVars,
                    state_vars endStateVars) {
    // lol

}

const int numTests = 0
const state testStatesIn[numTests] = {};
const state testStatesOut[numTests] = {};
const state_inputs testInputs[numTests] = {};
const state_vars testVarsIn[numTests] = {};
const state_vars testVarsOut[numTests] = {};


/*
 * Runs through all the FSM tests
 */
bool testAllTests() {
  for (int i = 0; i < numTests; i++) {
    Serial.print("Running test ");
    Serial.println(i);
    if (!testTransition(testStatesIn[i], testStatesOut[i], testInputs[i], testVarsIn[i], testVarsOut[i], true)) {
      return false;
    }
    Serial.println();
  }
  Serial.println("All tests passed!");
  return true;
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