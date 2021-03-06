//Alternate LEDs from Off, Green, and Red
#include <msp430.h>
#include "libTimer.h"
#include "led.h"
#include "stateMachines.h"
#include "buzzer.h"
#include "switches.h"


int main(void) {
  configureClocks();		/* setup master oscillator, CPU & peripheral clocks */
  led_init();
  enableWDTInterrupts();	/* enable periodic interrupt */
  buzzer_init();
  switch_init();
  sound();
  

  or_sr(0x18);		/* CPU off, GIE on */
}
