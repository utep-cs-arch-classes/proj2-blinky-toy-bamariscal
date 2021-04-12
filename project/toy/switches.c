#include <msp430.h>
#include "switches.h"
#include "led.h"
#include "stateMachines.h"


char switch_state_down, switch_state_changed; /* effectively boolean */
//int sound;

static char 
switch_update_interrupt_sense()
{
  char p1val = P1IN;
  /* update switch interrupt to detect changes from current buttons */
  P1IES |= (p1val & SWITCHES);	/* if switch up, sense down */
  P1IES &= (p1val | ~SWITCHES);	/* if switch down, sense up */
  return p1val;
}

void 
switch_init()			/* setup switch */
{  
  P1REN |= SWITCHES;		/* enables resistors for switches */
  P1IE |= SWITCHES;		/* enable interrupts from switches */
  P1OUT |= SWITCHES;		/* pull-ups for switches */
  P1DIR &= ~SWITCHES;		/* set switches' bits for input */
  switch_update_interrupt_sense();
  switch_interrupt_handler();
  led_update();
}


void
switch_interrupt_handler()
{
  char p1val = switch_update_interrupt_sense();
  switch_state_down = (p1val & SW1) ? 0 : 1; /* 0 when SW1 is up */
  char button1 = (p1val & SW1) ? 0 :SW1;
  char button2 = (p1val & SW2) ? 0 :SW2;
  char button3 = (p1val & SW3) ? 0 :SW3;
  char button4 = (p1val &SW4) ? 0 : SW4;
  
  if(button1){
    sound(500);
    led_changed = 1;
    state_advance();
    led_update();
  }

 if(button2){
    sound(1000);
    led_changed = 1;
    state_advance();
    led_update();
  }

  if(button3){
    sound(1500);
    led_changed = 1;
    state_advance();
    led_update();
  }

  if(button4){
    sound(2000);
    led_changed = 1;
    state_advance();
    led_update();
  }


}
