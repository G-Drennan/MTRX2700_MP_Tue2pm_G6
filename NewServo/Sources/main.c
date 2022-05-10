#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */


#include "servo.h"
#include "timer.h"


void main(void) {
  /* put your own code here */
  PWMinitialise();

  //(start angle, end angle, steps)
  elevation(0, 90, 1);
  delay(100);
  elevation(90, 0, 1);
  delay(100);  
  azimuth(-90, 90, 1);
  delay(100);  
  azimuth(90, 0, 1);
  delay(100);
  setServoPose(45, 45);
  delay(100);
	EnableInterrupts;


  for(;;) {
    _FEED_COP(); /* feeds the dog */
  } /* loop forever */
  /* please make sure that you never leave main */
}
