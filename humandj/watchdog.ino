// unsigned int getNextCPUINT(unsigned int start) {
//    unsigned int tryInt = start + 1;
//       while (tryInt < 32) {
//          if (NVIC_GetEnableIRQ((IRQn_Type) tryInt) == 0) {
//             return tryInt;
//          }
//       tryInt++;
//    }
// }

// /* Initialize the WDT peripheral */
// void initWDT() {
//   unsigned int WDT_INT = getNextCPUINT(0);

//   // TODO step 3 (prelab Qs6.1-6.2)
//   // Remember to use a 100% refresh window, unlike the prelab!
//   R_WDT->WDTCR = 0b0011001110000010;

//   // Enable WDT when debugger is connected
//   R_DEBUG->DBGSTOPCR_b.DBGSTOP_WDT = 0;
//   R_WDT->WDTSR = 0; // clear watchdog status;

//   // TODO step 3 (prelab Qs6.4-6.5): Make the watchdog trigger an interrupt
//   // and use the ICU to connect it to the CPU
//   // Make sure to call the correct CMSIS functions as well!
//   R_WDT->WDTRCR = 0b10000000;
//   R_ICU->IELSR[WDT_INT] = 0x025;

//   NVIC_SetVector((IRQn_Type) WDT_INT, (uint32_t) &wdtISR); // set vector entry to our handler
//   NVIC_SetPriority((IRQn_Type) WDT_INT, 13); // Priority lower than Serial (12)
//   NVIC_EnableIRQ((IRQn_Type) WDT_INT);
// }

// /* pet the watchdog */
// void petWDT() {
//   // TODO step 3 (prelab Q6.3)
//   R_WDT->WDTRR = 0;
//   R_WDT->WDTRR = 0xff;

// }

// /* ISR when WDT triggers */
// void wdtISR() {
//   Serial.println("[ERROR] Watchdog triggered!");
//   while(true);
// }