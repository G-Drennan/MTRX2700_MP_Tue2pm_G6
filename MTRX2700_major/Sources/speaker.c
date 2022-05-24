#include "speaker.h"

#include "derivative.h"

int period;
int duration; 


void play_note(int play){
  // Disable all interrupts
	asm(sei);
	
	// Enable timer and fast flag clear
	TSCR1 = 0x90; 
	
	// Set prescaler to 8
	TSCR2 = 0x03;
	
	// Choose output compare for channel 5
	TIOS = 0x20;
	
	// Toggle upon successful output compare 
	TCTL1 = 0x04; 
	
	// Set first output compare to happen
	period = 0;        //assume no-one is in the way
	if (play == 1){    // if someone is in the way make noise
	  period = 34110;  
	}
	TC5 = TCNT + period;
	asm(cli);

  // Enable interrupts for timer 5
	TIE = 0x20;
}


void delay_ms(unsigned int time){
    int i,j;
    for(i=0;i<time;i++)
      for(j=0;j<4000;j++);
}

#pragma CODE_SEG __NEAR_SEG NON_BANKED
__interrupt void TC5_ISR() 
{
  TC5 = TC5 + period;
}

