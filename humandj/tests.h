
/*
 * TODO: A struct to keep all state inputs in one place
 */
typedef struct {

} state_inputs;


/*
 * TODO: A struct to keep all state variables in one place
 */
typedef struct {
  
} state_vars;

bool testTransition(state startState,
                     state endState,
                     state_inputs testStateInputs, 
                     state_vars startStateVars,
                     state_vars endStateVars,
                     bool verbos);

