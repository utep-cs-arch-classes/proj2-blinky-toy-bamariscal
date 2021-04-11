#include <msp430.h>
#include "stateMachines.h"

void
__interrupt_vec(WDT_VECTOR) WDT(){	/* 250 interrupts/sec */
  static char blink_count = 0;
  if (++blink_count == 200){
    clock_one();
    state_advance();
    blink_count = 0;
  }

  clock_two();
  update_lights();
  
  led_update();
}
