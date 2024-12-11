/*
 * For human dj fsm testing
 */
// #include "tests.h"

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



// /*
// TODO
// */
// bool testTransition(state startState,
//                      state endState,
//                      state_inputs testStateInputs, 
//                      state_vars startStateVars,
//                      state_vars endStateVars,
//                      bool verbos) {

// }

// /*
//  * TODO: add in test cases
//  */

// // const int numTests = 23;


// /*
//  * Runs through all the FSM tests
//  */
// bool testAllTests() {
//   for (int i = 0; i < numTests; i++) {
//     Serial.print("Running test ");
//     Serial.println(i);
//     if (!testTransition(testStatesIn[i], testStatesOut[i], testInputs[i], testVarsIn[i], testVarsOut[i], true)) {
//       return false;
//     }
//     Serial.println();
//   }
//   Serial.println("All tests passed!");
//   return true;
// }

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