#include <msp430.h>
#include "stateMachines.h"
#include "led.h"
#include "switches.h"

static enum {off =0, light = 1, dim =2} ledStyle;
static char count = 0;

void clock_one(){
  ledStyle = (ledStyle +1)%4;
}

void clock_two(){
  count = (count+1)&4;
}

void update_lights(){
  char red_two;

  switch (ledStyle){
  case off:
    red_two = 0;
    break;
  case light:
    red_two = 1;
    break;
  case dim:
    red_two = (count <1);
    break;
  }

  if(red_on != red_two){
    red_on = red_two;
    led_changed =1;
  }
}
  

char toggle_red()		/* always toggle! */
{
  static char state = 0;

  switch (state) {
  case 0:
    red_on = 1;
    state = 1; 
    break;
  case 1:
    red_on = 0;
    green_on = 0;
    state = 0;
    break;
  }
    
  return 1;			/* always changes, an led */
}

char toggle_green()	/* only toggle green if red is on!  */
{
  char changed = 0;
  if (green_on) {
    red_on ^= 1;
    changed = 1;
  }
  return changed;
}

char on_both(){
  char changed = 0;
  red_on = 1;
  green_on = 1;
  changed =1;
 
  return changed;
}


void state_advance()		/* alternate between toggling red & green */
{
  char changed = 0;  
 
  static enum {R=0, G=1,B =2} color = B;
  switch (color) {
  case R:
    changed = toggle_red();
    color = B;
    break;
  case B:
    changed = on_both();
    color = G;
    break;
  case G:
    changed = toggle_green();
    color = R;
    break;
     }

  led_changed = changed;
  led_update();
}
