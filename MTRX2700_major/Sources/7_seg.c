#include "derivative.h"

#include "7_seg.h"
#include "functions.h"

//display the current state to the 7 -seg as visual indication process is working 
void display(void){
  int seg_values_arr[10] = { 0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F}; // store 7-seg values for 0-9
  
  PORTB = seg_values_arr[current_state]; //displayed on 7-seg
  
  //0x06
}
// initailise 7-seg
void seg7Initialise(void){
    DDRB = 0xFF;      // set port B and D to outputs
    DDRP = 0xFF; 
    
    PTP = 0xFE; // turn the left-most 7-seg 11111110  
}
