/*
TODO
called within setup?
*/
void init_wdt() {

  NVIC_DisableIRQ(WDT_IRQn);
  NVIC_ClearPendingIRQ(WDT_IRQn);
  NVIC_SetPriority(WDT_IRQn, 0);
  NVIC_EnableIRQ(WDT_IRQn);

  // Configure generic clock controller for WDT 
  GCLK->GENDIV.reg = GCLK_GENDIV_DIV(4) | GCLK_GENDIV_ID(5);
  while (GCLK->STATUS.bit.SYNCBUSY);

  GCLK->GENCTRL.reg = GCLK_GENCTRL_DIVSEL | GCLK_GENCTRL_ID(5) | GCLK_GENCTRL_GENEN | GCLK_GENCTRL_SRC(3);
  GCLK->CLKCTRL.reg = GCLK_CLKCTRL_GEN(5) | GCLK_CLKCTRL_CLKEN | GCLK_CLKCTRL_ID(3);
  while (GCLK->STATUS.bit.SYNCBUSY);

  // Watchdog timer ~4 seconds w/ early warning ~2 seconds
  WDT->CONFIG.reg = WDT_CONFIG_PER(9);
  WDT->EWCTRL.reg = WDT_EWCTRL_EWOFFSET(8);
  WDT->CTRL.reg |= WDT_CTRL_ENABLE;

  // Enable early warning interrupts on WDT
  WDT->INTENSET.reg |= WDT_INTENSET_EW;
  while (WDT->STATUS.bit.SYNCBUSY);
}

/* 
TODO 
called at some point in loop
 */
void pet_wdt() {
  if (DEBUG){
    // Serial.println("petting watchdog");
  }
  WDT->CLEAR.reg = 0xA5;
  while(WDT->STATUS.bit.SYNCBUSY);

}

void wdt_handler() {
  // Clear interrupt register flag
  WDT->INTFLAG.reg = 1;
  
  // Warn user that a watchdog reset may happen
  if (DEBUG){
    Serial.println("WATCHDOG ABOUT TO BARK\n");
  }
}