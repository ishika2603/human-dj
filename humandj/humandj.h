
/*
 * Type (enum and struct) definitions for state, orientation,
 * (xy) coordinate, (xyo) coordinate, (upper, lower) bounds
 */
typedef enum {
  sINIT = 1,
  sWAIT_FOR_CHANGE = 2,
  sSEND_START_NOTE = 3,
  sSEND_END_NOTE = 4,
  sSEND_SLIDER_CHANGE = 5,
} state;


state updateFSM();
